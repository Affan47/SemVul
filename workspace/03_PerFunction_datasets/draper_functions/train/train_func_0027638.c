photos_selection_toolbar_collection_clicked (GtkButton *button, gpointer user_data)
{
  PhotosSelectionToolbar *self = PHOTOS_SELECTION_TOOLBAR (user_data);
  GtkWidget *dialog;
  GtkWidget *toplevel;

  toplevel = gtk_widget_get_toplevel (GTK_WIDGET (self));
  if (!gtk_widget_is_toplevel (toplevel))
    return;

  dialog = photos_organize_collection_dialog_new (GTK_WINDOW (toplevel));
  gtk_widget_show_all (dialog);
  g_signal_connect (dialog, "response", G_CALLBACK (photos_selection_toolbar_dialog_response), self);
}
