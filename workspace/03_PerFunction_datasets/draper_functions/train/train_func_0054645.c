entry_changed_cb (GtkEntry * entry, char **str)
{
  const gchar *s;

  s = gtk_entry_get_text (entry);

  if (*str)
    free (*str);
  *str = strdup (s);

  clear_auto ();
}
