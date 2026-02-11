ho_font_pnm_save (const ho_bitmap * m_text, const ho_bitmap * m_nikud,
  const ho_bitmap * m_mask, const char *filename)
{
  FILE *file = NULL;
  ho_pixbuf *pix = NULL;
  int x, y;
  unsigned char red, green, blue;


  pix = ho_pixbuf_new (3, m_text->width, m_text->height, 0);
  if (!pix)
    return TRUE;


  for (x = 0; x < m_text->width; x++)
    for (y = 0; y < m_text->height; y++)
    {
      red = ho_bitmap_get (m_text, x, y) * 255;
      green = ho_bitmap_get (m_nikud, x, y) * 255;
      blue = ho_bitmap_get (m_mask, x, y) * 255;

      ho_pixbuf_set (pix, x, y, 0, red);
      ho_pixbuf_set (pix, x, y, 1, green);
      ho_pixbuf_set (pix, x, y, 2, blue);
    }


  file = fopen (filename, "wb");

  if (!file)
  {
    ho_pixbuf_free (pix);
    return TRUE;
  }


  fprintf (file, "P6 %d %d 255\n", pix->width, pix->height);


  fwrite (pix->data, 1, pix->height * pix->rowstride, file);
  fclose (file);

  ho_pixbuf_free (pix);

  return FALSE;
}
