onScriptChosen(GtkFileChooserButton *widget, gpointer user_data)
{
  gchar *file;

  file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));
  gtk_widget_set_sensitive(GTK_WIDGET(user_data), (file != (gchar*)0));
  if (file)
    g_free(file);
}
