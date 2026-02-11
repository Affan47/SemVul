p_filesel_tabw_ok (GtkWidget *widget
                   ,GapStbTabWidgets *tabw)
{
  const gchar *filename;
  gboolean     rc;

  rc = FALSE;
  if(tabw == NULL) return (rc);
  if(tabw->filesel == NULL) return (rc);

  filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (tabw->filesel));
  if(filename)
  {
    if(tabw->filename_refptr)
    {
      g_snprintf(tabw->filename_refptr
              , tabw->filename_maxlen
              , "%s"
              , filename
              );
      gtk_entry_set_text(GTK_ENTRY(tabw->filename_entry), filename);
    }
    rc = TRUE;
  }

  gtk_widget_destroy(GTK_WIDGET(tabw->filesel));
  tabw->filesel = NULL;

  return(rc);
}
