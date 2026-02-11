ho_pixbuf_color_to_red (const ho_pixbuf * pix)
{
  ho_pixbuf *pix_red = NULL;
  int x, y;
  unsigned char red;


  if (pix->n_channels < 3)
    return NULL;


  pix_red = ho_pixbuf_new (1, pix->width, pix->height, 0);
  if (!pix_red)
    return NULL;

  for (x = 0; x < pix->width; x++)
    for (y = 0; y < pix->height; y++)
    {
      red = ho_pixbuf_get (pix, x, y, 0);

      ho_pixbuf_set (pix_red, x, y, 0, red);
    }

  return pix_red;
}
