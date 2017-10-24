#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<ESP8266mDNS.h>

ESP8266WebServer server(80);

int led_pin = LED_BUILTIN;
char* username = "IE-NITK";
char* password = "workshop";
String html_page;
String msg = "0", led_status = "0";
int count = 0;
void setup()
{
  WiFi.begin(username, password);
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
  server.on("/", send_html);
  server.on("/ledon", led_on);
  server.on("/ledoff", led_off);
  server.begin();
}


void loop()
{

  server.handleClient();
}

void send_html()
{
  String html_page = "<!DOCTYPE html> <html> <head> <title>IE - NITK</title> <meta http-equiv=\"refresh\" content=\"5\"> </head> <style type=\"text/css\"> .center{ text-align: center; } .head-color{ color : #092040; } input[type=submit] { background-color: #008CBA; border: none; color: white; padding: 16px 32px; cursor: pointer; margin:auto; margin-bottom: 20px; display: block; } </style> <body> <h1 class = \"center head-color\"><strong>IE GADGET - WORKSHOP</strong></h1><br><br> <h2 class = \"center head-color\"> Count : ";
  html_page += msg;
  html_page += " </h2> <h2 class = \"center head-color\"> Led Status : ";
  html_page += led_status;
  html_page += " </h2> <form action = \"ledon\" class=\"center\" method=\"GET\"> <input type=\"submit\" value=\"led on\"/> </form> <form action = \"ledoff\" class=\"center\" method=\"GET\"> <input type=\"submit\" value=\"led off\"/> </form> </body> </html>";

  server.send(200, "text/html", html_page);
}

void led_on()
{
  if(led_status == "OFF")
  {
    count++;
  }
  digitalWrite(led_pin, HIGH);
  led_status = "ON";
  msg = (String)count;
  send_html();
}

void led_off()
{
  digitalWrite(led_pin, LOW);
  led_status = "OFF";
  send_html();
}

