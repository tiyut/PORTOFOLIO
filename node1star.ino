//node1
#include <SPI.h>              // include libraries
#include <LoRa.h>


const int csPin = 7;          // LoRa radio chip select
const int resetPin = 6;       // LoRa radio reset
const int irqPin = 1;         // change for your board; must be a hardware interrupt pin
String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 2000; 

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);                   // initialize serial
  while (!Serial);

  Serial.println("LoRa Duplex");

  // override the default CS, reset, and IRQ pins (optional)
//  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(915E6)) {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }
  Serial.println("LoRa init succeeded.");
  LoRa.setSpreadingFactor(9);
  LoRa.setCodingRate4(5);
}

void loop() {
  String bundlepackage;
  // put your main code here, to run repeatedly:
   if (millis() - lastSendTime > interval) {
    bundlepackage="iamnode1,8811";
    sendMessage(bundlepackage);
    lastSendTime = millis();            // timestamp the message // 2 seconds
  }
  delay(2000);
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  Serial.println("Sending " + outgoing);
  Serial.println();
}
