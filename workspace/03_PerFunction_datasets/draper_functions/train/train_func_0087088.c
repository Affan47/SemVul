create_update_data (void)
{
  uint8_t *data = g_malloc (256 * 256 * 4), *p = data;
  int x, y;


  for (y = 0; y < 256; y++)
    for (x = 0; x < 256; x++)
      {
        *(p++) = 0;
        *(p++) = 0;
        *(p++) = x;
        *(p++) = y;
      }

  return data;
}
