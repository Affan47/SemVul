stop_message(GtkWidget * widget, gpointer * data)
{

  stop_tx();

  gtk_widget_hide(time_left_desc_la);
  gtk_widget_hide(time_left_la);

  gtk_editable_set_editable(GTK_EDITABLE(entry), TRUE);

  gtk_widget_set_sensitive(start_button, TRUE);
  gtk_widget_set_sensitive(stop_button, FALSE);

  if (function_tag != 0)
    gtk_timeout_remove(function_tag);
}
