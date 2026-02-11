on_bootproto_changed (GtkWidget *widget, gpointer data)
{
  GstConnectionDialog *dialog;
  gchar *method;
  gboolean enabled;

  dialog = GST_NETWORK_TOOL (tool)->dialog;
  method = connection_combo_get_value (GTK_COMBO_BOX (dialog->bootproto_combo));
  enabled = (method && strcmp (method, "static") == 0);

  gtk_widget_set_sensitive (dialog->address, enabled);
  gtk_widget_set_sensitive (dialog->netmask, enabled);
  gtk_widget_set_sensitive (dialog->gateway, enabled);

  g_free (method);
}
