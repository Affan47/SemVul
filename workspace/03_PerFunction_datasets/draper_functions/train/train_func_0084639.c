xlib_rgb_convert_0888_br (XImage *image,
			 int ax, int ay, int width, int height,
			 unsigned char *buf, int rowstride,
			 int x_align, int y_align, XlibRgbCmap *cmap)
{
  int x, y;
  unsigned char *obuf;
  int bpl;
  unsigned char *bptr, *bp2;
  int r, g, b;

  bptr = buf;
  bpl = image->bytes_per_line;
  obuf = ((unsigned char *)image->data) + ay * bpl + ax * 4;
  for (y = 0; y < height; y++)
    {
      bp2 = bptr;
      for (x = 0; x < width; x++)
	{
	  r = bp2[0];
	  g = bp2[1];
	  b = bp2[2];
	  ((guint32 *)obuf)[x] = (b << 24) | (g << 16) | (r << 8);
	  bp2 += 3;
	}
      bptr += rowstride;
      obuf += bpl;
    }
}
