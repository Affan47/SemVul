ho_pixbuf_new (const unsigned char n_channels,
  const int width, const int height, const int rowstride)
{
  ho_pixbuf *pix = NULL;


  pix = (ho_pixbuf *) malloc (sizeof (ho_pixbuf));
  if (!pix)
  {
    return NULL;
  }


  pix->n_channels = n_channels;
  pix->width = width;
  pix->height = height;
  if (rowstride)
    pix->rowstride = rowstride;
  else
    pix->rowstride = width * n_channels;


  pix->data = malloc (pix->height * pix->rowstride);
  if (!(pix->data))
  {
    free (pix);
    return NULL;
  }

  memset ((void *) (pix->data), 255, pix->height * pix->rowstride);

  return pix;
}
