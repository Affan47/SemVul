ho_pixbuf_to_rgb (const ho_pixbuf * pix_in)
{
  int x, y;
  ho_pixbuf *pix = NULL;
  unsigned char red, green, blue;


  pix = ho_pixbuf_new (3, pix_in->width, pix_in->height, 0);
  if (!pix)
    return NULL;


  if (pix_in->n_channels < 3)
  {

    for (x = 0; x < pix_in->width; x++)
      for (y = 0; y < pix_in->height; y++)
      {
        red = ho_pixbuf_get (pix_in, x, y, 0);
        ho_pixbuf_set (pix, x, y, 0, red);
        ho_pixbuf_set (pix, x, y, 1, red);
        ho_pixbuf_set (pix, x, y, 2, red);
      }

  }
  else
  {

    for (x = 0; x < pix_in->width; x++)
      for (y = 0; y < pix_in->height; y++)
      {
        red = ho_pixbuf_get (pix_in, x, y, 0);
        green = ho_pixbuf_get (pix_in, x, y, 1);
        blue = ho_pixbuf_get (pix_in, x, y, 2);
        ho_pixbuf_set (pix, x, y, 0, red);
        ho_pixbuf_set (pix, x, y, 1, green);
        ho_pixbuf_set (pix, x, y, 2, blue);
      }
  }

  return pix;
}
