knocker_led_turn_on (int led)
{
#ifndef NO_LED
  char state;

  if (!initialized)
    knocker_led_init (&knocker_led_status);

  ioctl (0, KDGETLED, &state);

  if (led == KNOCKER_LED_NUMLOCK)
    {
      if (!knocker_led_status.num)
        {
          ioctl (0, KDSETLED, LED_VALUE_NUM);
          knocker_led_status.num = 1;
        }
    }
  else if (led == KNOCKER_LED_CAPSLOCK)
    {
      if (!knocker_led_status.caps)
        {
          ioctl (0, KDSETLED, LED_VALUE_CAP);
          knocker_led_status.caps = 1;
        }
    }
  else if (led == KNOCKER_LED_SCROLLOCK)
    {
      if (!knocker_led_status.scroll)
        {
          ioctl (0, KDSETLED, LED_VALUE_SCR);
          knocker_led_status.scroll = 1;
        }
    }
#endif
  return;
}
