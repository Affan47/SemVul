sw_item_stream_add_item (SwItemStream *item_stream,
                         SwItem       *item)
{
  SwItemStreamPrivate *priv = GET_PRIVATE (item_stream);
  GValueArray *value_array;
  GPtrArray *ptr_array;

  ptr_array = g_ptr_array_new_with_free_func ((GDestroyNotify)g_value_array_free);

  if (sw_item_get_ready (item))
  {
    SW_DEBUG (VIEWS, "Item ready: %s",
              sw_item_get (item, "id"));
    value_array = _sw_item_to_value_array (item);
    g_ptr_array_add (ptr_array, value_array);
  } else {
    SW_DEBUG (VIEWS, "Item not ready, setting up handler: %s",
              sw_item_get (item, "id"));
    _setup_ready_handler (item, item_stream);
    sw_set_add (priv->pending_items_set, (GObject *)item);
  }

  _setup_changed_handler (item, item_stream);

  sw_item_view_iface_emit_items_added (item_stream,
                                         ptr_array);

  g_ptr_array_free (ptr_array, TRUE);
}
