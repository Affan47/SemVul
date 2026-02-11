generate_bit (unsigned char alpha[], GdkColor *color, double mult)
{
  guint r, g, b;
  GdkPixbuf *pixbuf;
  unsigned char *pixels;
  int w, h, rs;
  int x, y;

  r = (color->red >> 8) * mult;
  r = MIN(r, 255);
  g = (color->green >> 8) * mult;
  g = MIN(g, 255);
  b = (color->blue >> 8) * mult;
  b = MIN(b, 255);

  pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8, RADIO_SIZE, RADIO_SIZE);

  w = gdk_pixbuf_get_width (pixbuf);
  h = gdk_pixbuf_get_height (pixbuf);
  rs = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);


  for (y=0; y < h; y++)
    {
      for (x=0; x < w; x++)
	{
	  pixels[y*rs + x*4 + 0] = r;
	  pixels[y*rs + x*4 + 1] = g;
	  pixels[y*rs + x*4 + 2] = b;
	  if (alpha)
	    pixels[y*rs + x*4 + 3] = alpha[y*w + x];
	  else
	    pixels[y*rs + x*4 + 3] = 255;
	}
    }

  return pixbuf;
}
