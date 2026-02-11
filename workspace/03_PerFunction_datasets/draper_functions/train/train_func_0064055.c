spin_to_entry (GtkSpinButton * sb, gchar * entry_name, guint8 * base)
{
  GtkEntry *entry;
  gint val, addr;
  gchar s[10] = "";
  g_assert (base);
  g_assert (sb);
  g_assert (entry_name);


  entry = GTK_ENTRY (lookup_widget (app->window_main, entry_name));
  g_assert (entry);

  addr = gtk_spin_button_get_value (GTK_SPIN_BUTTON (sb));
  g_assert (0 <= addr && addr < 65536);
  val = base[addr];

  g_ascii_dtostr (s, 10, val);


  gtk_entry_set_text (entry, s);
}
