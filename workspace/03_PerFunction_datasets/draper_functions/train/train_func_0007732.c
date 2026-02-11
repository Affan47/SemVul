genesys_average_black (Genesys_Device * dev, int channel,
		       uint8_t * data, int pixels)
{
  int i;
  int sum;
  int pixel_step;

  DBG (DBG_proc, "genesys_average_black: channel=%d, pixels=%d\n",
       channel, pixels);

  sum = 0;

  if (dev->settings.scan_mode == SCAN_MODE_COLOR)
    {
      data += (channel * 2);
      pixel_step = 3 * 2;
    }
  else
    {
      pixel_step = 2;
    }

  for (i = 0; i < pixels; i++)
    {
      sum += *data;
      sum += *(data + 1) * 256;

      data += pixel_step;
    }

  DBG (DBG_proc, "genesys_average_black = %d\n", sum / pixels);

  return (int) (sum / pixels);
}
