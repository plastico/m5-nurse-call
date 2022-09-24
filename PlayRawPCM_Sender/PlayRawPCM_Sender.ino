/*
*******************************************************************************
  Copyright (c) 2021 by M5Stack
                   Equipped with Atom-Lite sample source code
                           配套  Atom-Lite 示例源代码
  Visit the website for more information：https://docs.m5stack.com/en/atom/atom_spk
  获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atom_spk

  describe: SPK.
  date：2021/9/1

  Modified by Hiroyuki Abe 2022 for inhouse call system (Sender side)
*******************************************************************************
  Use ATOM SPK Compile and play PCM files.  使用ATOM SPK编译和播放PCM文件
*/
#include "M5Atom.h"
#include <esp_now.h>
#include <WiFi.h>

uint8_t slaveAddress[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }; // broadcast.  You can change reciever address.
esp_now_peer_info_t slave;

void setup() {
  Serial.begin(115200);
  M5.begin(true, false, true);

  Serial.println(WiFi.macAddress());
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESP-Now Init Success");
  }

  M5.dis.drawpix(0, 0x00ff00);

  slave.peer_addr[0] = (uint8_t)0xff;
  slave.peer_addr[1] = (uint8_t)0xff;
  slave.peer_addr[2] = (uint8_t)0xff;
  slave.peer_addr[3] = (uint8_t)0xff;
  slave.peer_addr[4] = (uint8_t)0xff;
  slave.peer_addr[5] = (uint8_t)0xff;
  slave.channel = 0;
  slave.encrypt = false;

  esp_err_t addStatus = esp_now_add_peer(&slave);
}



void loop() {
  char     buf[250];
  uint8_t bs[250];

  if (M5.Btn.wasPressed()) {

    M5.dis.drawpix(0, 0xff0000);

    sprintf(buf, "#");
    memcpy(bs, buf, strlen(buf));
    esp_err_t result = esp_now_send(slave.peer_addr, bs, strlen(buf));

  }
  if (M5.Btn.isReleased()) {

    M5.dis.drawpix(0, 0x00ff00);

  }
  M5.update();
}
