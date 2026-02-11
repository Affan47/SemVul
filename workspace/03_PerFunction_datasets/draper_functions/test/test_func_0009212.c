compselect_callback_filter_entry_changed (GtkEditable *editable,
                                          gpointer  user_data)
{
  Compselect *compselect = COMPSELECT (user_data);
  GtkWidget *button;
  gboolean sensitive;


  button    = GTK_WIDGET (compselect->button_clear);
  sensitive =
    (g_ascii_strcasecmp (gtk_entry_get_text (compselect->entry_filter),
                         "") != 0);
  if (GTK_WIDGET_IS_SENSITIVE (button) != sensitive) {
    gtk_widget_set_sensitive (button, sensitive);
  }


  if (compselect->filter_timeout != 0)
    g_source_remove (compselect->filter_timeout);


  compselect->filter_timeout = g_timeout_add (COMPSELECT_FILTER_INTERVAL,
                                              compselect_filter_timeout,
                                              compselect);

}
