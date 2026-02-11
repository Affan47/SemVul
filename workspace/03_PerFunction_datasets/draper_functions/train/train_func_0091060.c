entry_focus_changed (GtkWidget  *w,
                     G_GNUC_UNUSED GdkEventFocus *ev,
                     gpointer data)
{
  gchar *key = NULL;
  gchar *current_value = NULL;

  key = (gchar *) data;

  current_value = gm_conf_get_string (key);

  if (!current_value
      || g_strcmp0 (current_value, gtk_entry_get_text (GTK_ENTRY (w)))) {

    gm_conf_set_string (key, (gchar *)gtk_entry_get_text (GTK_ENTRY (w)));
  }
  g_free (current_value);

  return FALSE;
}
