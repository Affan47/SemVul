on_mem_list_start_changed (GtkEntry *entry, gpointer user_data)
{
  gint start_addr;
  gchar *text;
  g_assert (entry);

  if (!asm_util_parse_number (text = (gchar *)gtk_entry_get_text (GTK_ENTRY (entry)),&start_addr))
  {
    gui_app_show_msg (GTK_MESSAGE_INFO, _("Enter a valid number within range (0-65535 or 0h-FFFFh)"));
    return;
  }
  gui_list_memory_set_start (start_addr);
  gui_list_memory_update ();
  text[strlen (text)] = 'h';
  gtk_entry_set_text (GTK_ENTRY (entry), text);
}
