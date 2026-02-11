close_cb (GtkWidget *widget, gpointer data)
{
  if (data)
    *((gboolean *)data) = FALSE;
  gtk_widget_hide (widget);
  return TRUE;
}
