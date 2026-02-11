p_filesel_ok_callback(GtkWidget *widget,
                   fmac_globalparams_t *gpp)
{
  const gchar        *filename;

  if(gpp == NULL) return;

  filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (gpp->filesel));

  g_snprintf(&gpp->filtermacro_file[0], sizeof(gpp->filtermacro_file), "%s", filename);
  gtk_entry_set_text(GTK_ENTRY(gpp->file_entry), filename);

  if (gap_debug) printf("p_filesel_ok_callback: %s\n", gpp->filtermacro_file);

  p_filesel_close_callback(gpp->filesel, gpp);
}
