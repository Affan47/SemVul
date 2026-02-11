meta_gradient_create_vertical (int width, int height,
                               const GdkRGBA *from,
                               const GdkRGBA *to)
{
  int i, j;
  long r, g, b, dr, dg, db;
  GdkPixbuf *pixbuf;
  unsigned char *ptr;
  int r0, g0, b0;
  int rf, gf, bf;
  int rowstride;
  unsigned char *pixels;

  pixbuf = blank_pixbuf (width, height, FALSE);
  if (pixbuf == NULL)
    return NULL;

  pixels = gdk_pixbuf_get_pixels (pixbuf);
  rowstride = gdk_pixbuf_get_rowstride (pixbuf);

  r0 = (guchar) (from->red * 0xff);
  g0 = (guchar) (from->green * 0xff);
  b0 = (guchar) (from->blue * 0xff);
  rf = (guchar) (to->red * 0xff);
  gf = (guchar) (to->green * 0xff);
  bf = (guchar) (to->blue * 0xff);

  r = r0<<16;
  g = g0<<16;
  b = b0<<16;

  dr = ((rf-r0)<<16)/(int)height;
  dg = ((gf-g0)<<16)/(int)height;
  db = ((bf-b0)<<16)/(int)height;

  for (i=0; i<height; i++)
    {
      ptr = pixels + i * rowstride;

      ptr[0] = (unsigned char)(r>>16);
      ptr[1] = (unsigned char)(g>>16);
      ptr[2] = (unsigned char)(b>>16);

      for (j=1; j <= width/2; j *= 2)
        memcpy (&(ptr[j*3]), ptr, j*3);
      memcpy (&(ptr[j*3]), ptr, (width - j)*3);

      r+=dr;
      g+=dg;
      b+=db;
    }
  return pixbuf;
}
