ho_pixbuf_linear_filter (const ho_pixbuf * pix)
{
  ho_pixbuf *pix_gray = NULL;
  int x, y;
  unsigned char min, max;


  if (pix->n_channels != 1)
    return NULL;


  pix_gray = ho_pixbuf_new (1, pix->width, pix->height, 0);
  if (!pix_gray)
    return NULL;

  ho_pixbuf_minmax (pix, &min, &max);
  for (x = 0; x < pix->width; x++)
    for (y = 0; y < pix->height; y++)
    {
      (pix_gray->data)[x + y * pix_gray->rowstride] =
        255 * ((pix->data)[x + y * pix->rowstride] - min) / (max - min);
    }

  return pix_gray;
}
