entry_activate_callback (GtkEntry *entry,
                          void     *data)
{
  EggFindBar *find_bar = EGG_FIND_BAR (data);

  if (find_bar->priv->search_string != NULL)
    egg_find_bar_emit_next (find_bar);
}
