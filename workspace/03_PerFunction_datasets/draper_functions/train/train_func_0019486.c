ho_pixbuf_bw_tiff_save (const ho_pixbuf * pix, const char *filename)
{
  ho_bitmap *m = NULL;


  m = ho_pixbuf_to_bitmap (pix, 0);
  if (!m)
    return TRUE;


  ho_bitmap_tiff_save (m, filename);


  ho_bitmap_free (m);

  return FALSE;
}
