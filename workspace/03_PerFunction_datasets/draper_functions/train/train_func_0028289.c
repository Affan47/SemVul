g15r_drawCircle (g15canvas * canvas, int x, int y, int r, int fill, int color)
{
  int xx, yy, dd;

  xx = 0;
  yy = r;
  dd = 2 * (1 - r);

  while (yy >= 0)
    {
      if (!fill)
	{
	  g15r_setPixel (canvas, x + xx, y - yy, color);
	  g15r_setPixel (canvas, x + xx, y + yy, color);
	  g15r_setPixel (canvas, x - xx, y - yy, color);
	  g15r_setPixel (canvas, x - xx, y + yy, color);
	}
      else
	{
	  g15r_drawLine (canvas, x - xx, y - yy, x + xx, y - yy, color);
	  g15r_drawLine (canvas, x - xx, y + yy, x + xx, y + yy, color);
	}
      if (dd + yy > 0)
	{
	  yy--;
	  dd = dd - (2 * yy + 1);
	}
      if (xx > dd)
	{
	  xx++;
	  dd = dd + (2 * xx + 1);
	}
    }
}
