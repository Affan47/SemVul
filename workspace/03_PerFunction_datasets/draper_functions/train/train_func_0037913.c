generic_draw_point(int x, int y, byte_t col, bool clear_cache)
{
  int space[4] = {
    2, 1, 0, 0
  };
  int len[4] = {
    4, 6, 8, 8
  };

  for (int yy = 0;yy < 4;yy++)
    for (int xx = 0;xx < len[yy];xx++)
      {
	generic_put_pixel(x + xx + space[yy], y - 4 + yy, col, clear_cache);
	generic_put_pixel(x + xx + space[yy], y - 4 + 7 - yy, col, clear_cache);
      }
}
