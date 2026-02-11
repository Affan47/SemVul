xlib_rgb_convert_gray4_d (XImage *image,
		       int ax, int ay, int width, int height,
		       unsigned char *buf, int rowstride,
		       int x_align, int y_align, XlibRgbCmap *cmap)
{
  int x, y;
  int bpl;
  unsigned char *obuf, *obptr;
  unsigned char *bptr, *bp2;
  int r, g, b;
  const unsigned char *dmp;
  int prec, right;
  int gray;

  bptr = buf;
  bpl = image->bytes_per_line;
  obuf = ((unsigned char *)image->data) + ay * bpl + ax;
  prec = image_info->x_visual_info->depth;
  right = 8 - prec;
  for (y = 0; y < height; y++)
    {
      bp2 = bptr;
      obptr = obuf;
      dmp = DM[(y_align + y) & (DM_HEIGHT - 1)];
      for (x = 0; x < width; x++)
	{
	  r = *bp2++;
	  g = *bp2++;
	  b = *bp2++;
	  gray = (g + ((b + r) >> 1)) >> 1;
	  gray += (dmp[(x_align + x) & (DM_WIDTH - 1)] << 2) >> prec;
	  obptr[0] = (gray - (gray >> prec)) >> right;
	  obptr++;
	}
      bptr += rowstride;
      obuf += bpl;
    }
}
