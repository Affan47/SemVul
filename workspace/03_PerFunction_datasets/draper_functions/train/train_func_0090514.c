ho_gtk_pixbuf_load (const char *filename)
{
  ho_pixbuf *pix = NULL;
  GdkPixbuf *gdk_pix = NULL;


  gdk_pix = gdk_pixbuf_new_from_file (filename, NULL);

  if (!gdk_pix)
  {
    return NULL;
  }


  pix = ho_gtk_pixbuf_from_gdk (gdk_pix);


  g_object_unref (gdk_pix);

  return pix;
}
