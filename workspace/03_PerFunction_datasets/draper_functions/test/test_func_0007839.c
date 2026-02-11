onBgImageSet(GtkFileChooserButton *filechooserbutton, gpointer data _U_)
{
  gchar *filename;

  DBG_fprintf(stderr, "Panel Fog & Bg: bg image changed.\n");
  filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
  if (!filename)
    return;
  g_idle_add(loadBgFile, (gpointer)filename);
  VISU_REDRAW_ADD;
}
