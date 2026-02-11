ho_pixbuf_scale (const ho_pixbuf * pix, const unsigned char scale)
{

  if (scale < 2 || pix->n_channels != 1 || pix->width < 3 || pix->height < 3)
    return NULL;

  if (scale == 2)
    return ho_pixbuf_scale2 (pix);

  if (scale == 3)
    return ho_pixbuf_scale3 (pix);

  if (scale == 4)
    return ho_pixbuf_scale4 (pix);


  if (scale > 4)
    return ho_pixbuf_scale8 (pix);

  return NULL;
}
