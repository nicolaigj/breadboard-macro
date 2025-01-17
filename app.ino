#include "Keyboard.h"

const int BUTTON_PIN_START = 2;
const int RED_PIN = 9;
const int GREEN_PIN = 11;
const int BLUE_PIN = 10
;
unsigned long debounceDelay = 50;
const int MACRO_COUNT = 6;

struct button
{
    bool state;
    bool lastState;
    int pin;
    String command;
    unsigned long lastDebounce;
} buttons[MACRO_COUNT];

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, LOW);

    for (int i = 0; i < MACRO_COUNT; i++)
    {
        buttons[i].lastState = LOW;
        buttons[i].pin = BUTTON_PIN_START + i;
        buttons[i].lastDebounce = 0;
        pinMode(buttons[i].pin, INPUT);
    }
    buttons[0].command = "git pull";
    buttons[1].command = "git commit ";
    buttons[2].command = "git push";
    buttons[3].command = "4 ";
    buttons[4].command = "5 ";
    buttons[5].command = "6 ";

    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    writeRGB(255, 0, 255);    
}

void loop()
{
    for (int i = 0; i < MACRO_COUNT; i++)
    {
        checkButton(buttons[i]);
    }
}

void checkButton(button &button)
{
    int reading = digitalRead(button.pin);

    if (reading != button.lastState)
    {
        button.lastDebounce = millis();
    }

    if ((millis() - button.lastDebounce) > debounceDelay)
    {
        if (reading != button.state)
        {
            button.state = reading;
            if (button.state == HIGH)
            {
                digitalWrite(LED_BUILTIN, HIGH);
                Keyboard.begin();
                Keyboard.println(button.command);
                Keyboard.end();
            }
        }
    }
    digitalWrite(LED_BUILTIN, LOW);
    button.lastState = reading;
}

void writeRGB(int red, int green, int blue){
    analogWrite(RED_PIN, red);
    analogWrite(GREEN_PIN, green);
    analogWrite(BLUE_PIN, blue);
}