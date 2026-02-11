clutter_text_password_char_cb (GObject    *object,
                               GParamSpec *pspec,
                               gpointer    user_data)
{
  StEntry *entry = ST_ENTRY (user_data);

  if (clutter_text_get_password_char (CLUTTER_TEXT (entry->priv->entry)) == 0)
    remove_capslock_feedback (entry);
}
