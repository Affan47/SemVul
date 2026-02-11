host_aliases_check_fields (void)
{
  GtkWidget     *address, *aliases, *ok_button;
  GtkTextBuffer *buffer;
  GtkTextIter    start, end;
  gboolean       valid;
  const gchar   *addr;
  gchar         *str;
  gint           address_type;

  address   = gst_dialog_get_widget (tool->main_dialog, "host_alias_address");
  aliases   = gst_dialog_get_widget (tool->main_dialog, "host_alias_list");
  ok_button = gst_dialog_get_widget (tool->main_dialog, "host_alias_ok_button");

  buffer  = gtk_text_view_get_buffer (GTK_TEXT_VIEW (aliases));
  gtk_text_buffer_get_bounds (buffer, &start, &end);
  str = gtk_text_buffer_get_text (buffer, &start, &end, TRUE);

  addr = gtk_entry_get_text (GTK_ENTRY (address));
  address_type = gst_filter_check_ip_address (addr);

  valid = ((address_type == GST_ADDRESS_IPV4 || address_type == GST_ADDRESS_IPV6)
	   && (str && *str));
  gtk_widget_set_sensitive (ok_button, valid);

  g_free (str);
}
