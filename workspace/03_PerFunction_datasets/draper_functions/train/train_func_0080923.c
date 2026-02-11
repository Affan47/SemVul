sw_item_put (SwItem *item, const char *key, const char *value)
{
  g_return_if_fail (SW_IS_ITEM (item));
  g_return_if_fail (key);

  if (value)
    g_hash_table_insert (item->priv->hash,
                         (gpointer)g_intern_string (key),
                         g_strdup (value));
  else
    g_hash_table_remove (item->priv->hash,
                         (gpointer)g_intern_string (key));

  sw_item_touch (item);
}
