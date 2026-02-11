draw_reversed_ball_bitmap (int radius, CONST int color)
{
  RawBitmapType   bbitmap;
  int             x, y, r, c;
  radius /= DIV;
  err = 0.0;
  bbitmap = CreateBitmap ((radius * 2), (radius * 2));
  for (y = 0; y < radius * 2; y++)
    for (x = 0; x < radius * 2; x++)
      {
	if ((x - radius) * (x - radius) + (y - radius) * (y - radius)
	    < (radius - 0.5) * (radius - 0.5))
	  {
	    r = (x - 3 * radius / 4) * (x - 3 * radius / 4) +
	      (y - radius / 4) * (y - radius / 4);
	    r = r * 32 / (1.5 * radius) / (1.5 * radius);
	    if (r > 31)
	      r = 31;
	    c = errdist (color + 16 + r / 2);
	    BSetPixel (bbitmap, x, y, c);
	  }
	else
	  {
	    err = 0.0;
	    BSetPixel (bbitmap, x, y, 0);
	  }
      }
  return (CompileBitmap (radius * 2, radius * 2, bbitmap));
}
