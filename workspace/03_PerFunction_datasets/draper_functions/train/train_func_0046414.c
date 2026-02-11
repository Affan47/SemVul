filename_get_configure (GtkWidget * chooser, guint type, ggobid * gg)
{
  extern const gchar *key_get (void);

  const gchar *key = key_get ();
  g_object_set_data (G_OBJECT (chooser), "action", GINT_TO_POINTER (type));
  g_object_set_data (G_OBJECT (chooser), key, gg);

  if (gg->input && gg->input->baseName) {
    gchar *cwd = g_get_current_dir();
    gchar *dir;
    if (g_path_is_absolute(gg->input->dirName))
      dir = g_strdup(gg->input->dirName);
    else
      dir = g_build_filename(cwd, gg->input->dirName, NULL);
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (chooser), dir);
    g_free(dir);
    g_free(cwd);
  }
}
