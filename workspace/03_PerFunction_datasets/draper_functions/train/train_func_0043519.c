average_area (int color, SANE_Byte * data, int width, int height,
	      float *ra, float *ga, float *ba)
{
  int x, y;
  float global, pixels;
  float rc, gc, bc;
  pixels = width * height;
  *ra = 0;
  *ga = 0;
  *ba = 0;
  rc = 0;
  gc = 0;
  bc = 0;
  if (color == SANE_TRUE)
    {
      for (y = 0; y < height; y++)
	{
	  for (x = 0; x < width; x++)
	    {
	      rc += data[3 * width * y + x];
	      gc += data[3 * width * y + x + 1];
	      bc += data[3 * width * y + x + 2];
	    }
	}
      global = (rc + gc + bc) / (3 * pixels);
      *ra = rc / pixels;
      *ga = gc / pixels;
      *ba = bc / pixels;
    }
  else
    {
      for (y = 0; y < height; y++)
	{
	  for (x = 0; x < width; x++)
	    {
	      gc += data[width * y + x];
	    }
	}
      global = gc / pixels;
      *ga = gc / pixels;
    }
  DBG (7, "average_area: global=%.2f, red=%.2f, green=%.2f, blue=%.2f\n",
       global, *ra, *ga, *ba);
  return global;
}
