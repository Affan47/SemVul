loadXMLFile(gpointer data)
{
  gchar *filename;
  GError *error;

  g_return_val_if_fail(VISU_UI_IS_VALUE_IO(data), FALSE);
  g_return_val_if_fail(VISU_UI_VALUE_IO(data)->ioOpen, FALSE);

  filename = g_object_get_data(G_OBJECT(data), "filename");
  g_return_val_if_fail(filename, FALSE);

  error = (GError*)0;
  if (!VISU_UI_VALUE_IO(data)->ioOpen(filename, &error))
    {
      visu_ui_raiseWarning
	(_("Import V_Sim values from a file."),
	 error->message, VISU_UI_VALUE_IO(data)->parent);
      g_error_free(error);
#if GTK_MAJOR_VERSION > 2 || GTK_MINOR_VERSION > 5
      gtk_file_chooser_unselect_all(GTK_FILE_CHOOSER(VISU_UI_VALUE_IO(data)->btExportOpen));
      gtk_widget_set_sensitive(VISU_UI_VALUE_IO(data)->btExportSave, FALSE);
#endif
    }
  g_free(filename);
  g_object_set_data(G_OBJECT(data), "filename", (gpointer)0);

  return FALSE;
}
