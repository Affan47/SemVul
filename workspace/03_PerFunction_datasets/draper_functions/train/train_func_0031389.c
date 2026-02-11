dir_changed(GtkWidget * widget, gpointer data)
{
  char * dir;


  dir = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(data));
  if (dir == NULL)
  {
    return;
  }


  if (is_project_dir(dir))
  {
    gtk_widget_activate(gtk_dialog_get_widget_for_response(GTK_DIALOG(data), GTK_RESPONSE_ACCEPT));
  }
}
