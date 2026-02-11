generic_update(Scanline *scanline, MemAccess *memaccess, bool clear_cache)
{

  for (int a = 0;a < NR_OF_LEDS;a++)
    {
      _data[a][_idx] = ((Ports6 *)porti)->get_led_value(a);

      byte_t led_value = 0;
      for (int b = 0;b < HISTORY_LEN;b++)
	led_value |= _data[a][b];

      generic_draw_digit(65 * a + 32, 12, a, led_value, clear_cache);
    }

  _idx = (_idx + 1) % HISTORY_LEN;
}
