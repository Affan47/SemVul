_proxy_items_removed_cb (DBusGProxy *proxy,
                         GPtrArray  *items,
                         gpointer    userdata)
{
  SwClientItemView *view = SW_CLIENT_ITEM_VIEW (userdata);
  SwClientItemViewPrivate *priv = GET_PRIVATE (view);
  gint i = 0;
  GList *items_list = NULL;

  for (i = 0; i < items->len; i++)
  {
    GValueArray *varray = (GValueArray *)g_ptr_array_index (items, i);
    const gchar *uid;
    SwItem *item;

    uid = g_value_get_string (g_value_array_get_nth (varray, 1));

    item = g_hash_table_lookup (priv->uuid_to_items,
                                uid);

    if (item)
    {

      items_list = g_list_append (items_list, sw_item_ref (item));
      g_hash_table_remove (priv->uuid_to_items, uid);
    }
  }


  g_signal_emit (view, signals[ITEMS_REMOVED_SIGNAL], 0, items_list);

  g_list_foreach (items_list, (GFunc)sw_item_unref, NULL);
  g_list_free (items_list);
}
