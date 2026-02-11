ho_pixbuf_scale8 (const ho_pixbuf * pix)
{
  ho_pixbuf *pix_scaled4 = NULL;
  ho_pixbuf *pix_scaled8 = NULL;

  pix_scaled4 = ho_pixbuf_scale4 (pix);
  if (!pix_scaled4)
    return NULL;

  pix_scaled8 = ho_pixbuf_scale2 (pix_scaled4);
  ho_pixbuf_free (pix_scaled4);

  return pix_scaled8;
}
