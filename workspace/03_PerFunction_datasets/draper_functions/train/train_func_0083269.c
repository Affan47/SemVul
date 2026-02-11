ho_pixbuf_scale2 (const ho_pixbuf * pix)
{
  ho_pixbuf *pix_scaled = NULL;
  int x, y;
  unsigned char neighbors[4];


  if (pix->n_channels != 1 || pix->width < 3 || pix->height < 3)
    return NULL;


  pix_scaled = ho_pixbuf_new (1, pix->width * 2 - 2, pix->height * 2 - 2, 0);
  if (!pix_scaled)
    return NULL;

  for (x = 0; x < pix->width - 1; x++)
    for (y = 0; y < pix->height - 1; y++)
    {
      neighbors[0] = (pix->data)[x + y * pix->rowstride];
      neighbors[1] = (pix->data)[x + 1 + y * pix->rowstride];
      neighbors[2] = (pix->data)[x + (y + 1) * pix->rowstride];
      neighbors[3] = (pix->data)[x + 1 + (y + 1) * pix->rowstride];

      (pix_scaled->data)[(x * 2) + (y * 2) * pix_scaled->rowstride] =
        neighbors[0];
      (pix_scaled->data)[(x * 2) + 1 + (y * 2) * pix_scaled->rowstride] =
        (neighbors[0] + neighbors[1]) / 2;
      (pix_scaled->data)[(x * 2) + ((y * 2) + 1) * pix_scaled->rowstride] =
        (neighbors[0] + neighbors[2]) / 2;
      (pix_scaled->data)[(x * 2) + 1 +
        ((y * 2) + 1) * pix_scaled->rowstride] =
        (neighbors[0] + neighbors[1] + neighbors[2] + neighbors[3]) / 4;
    }

  return pix_scaled;
}
