gtr_history_entry_load_history (GtrHistoryEntry * entry)
{
  gchar **items;
  gsize i;

  items = g_settings_get_strv (entry->priv->settings,
                               entry->priv->history_id);
  i = 0;

  gtk_combo_box_text_remove_all (GTK_COMBO_BOX_TEXT (entry));


  while (items[i] != NULL && *items[i] != '\0' &&
         i < entry->priv->history_length)
    {
      gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (entry), items[i]);
      i++;
    }

  g_strfreev (items);
}
