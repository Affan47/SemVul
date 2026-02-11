xlib_rgb_convert_truecolor_lsb (XImage *image,
			       int ax, int ay, int width, int height,
			       unsigned char *buf, int rowstride,
			       int x_align, int y_align,
			       XlibRgbCmap *cmap)
{
  int x, y;
  unsigned char *obuf, *obptr;
  int bpl;
  unsigned char *bptr, *bp2;
  int r, g, b;
  int r_right, r_left;
  int g_right, g_left;
  int b_right, b_left;
  int bpp;
  guint32 pixel;
  int i;

  r_right = 8 - image_info->red_prec;
  r_left = image_info->red_shift;
  g_right = 8 - image_info->green_prec;
  g_left = image_info->green_shift;
  b_right = 8 - image_info->blue_prec;
  b_left = image_info->blue_shift;
  bpp = image_info->bpp;
  bptr = buf;
  bpl = image->bytes_per_line;
  obuf = ((unsigned char *)image->data) + ay * bpl + ax * bpp;
  for (y = 0; y < height; y++)
    {
      obptr = obuf;
      bp2 = bptr;
      for (x = 0; x < width; x++)
	{
	  r = bp2[0];
	  g = bp2[1];
	  b = bp2[2];
	  pixel = ((r >> r_right) << r_left) |
	    ((g >> g_right) << g_left) |
	    ((b >> b_right) << b_left);
	  for (i = 0; i < bpp; i++)
	    {
	      *obptr++ = pixel & 0xff;
	      pixel >>= 8;
	    }
	  bp2 += 3;
	}
      bptr += rowstride;
      obuf += bpl;
    }
}
