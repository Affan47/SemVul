_got_videos_cb (RestProxyCall *call,
                const GError  *error,
                GObject       *weak_object,
                gpointer       user_data)
{
  SwYoutubeItemView *item_view = SW_YOUTUBE_ITEM_VIEW (weak_object);
  SwYoutubeItemViewPrivate *priv = GET_PRIVATE (item_view);
  SwService *service;
  RestXmlNode *root, *node;

  if (error) {
    g_message (G_STRLOC ": error from Youtube: %s", error->message);

    return;
  }

  root = xml_node_from_call (call, "Youtube");
  if (!root)
    return;

  node = rest_xml_node_find (root, "channel");
  if (!node)
    return;


  g_hash_table_remove_all (priv->thumb_map);

  service = sw_item_view_get_service (SW_ITEM_VIEW (item_view));

  for (node = rest_xml_node_find (node, "item"); node; node = node->next) {
    SwItem *item;
    item = make_item (item_view, service, node);

    if (!sw_service_is_uid_banned (service, sw_item_get (item, "id"))) {
      sw_set_add (priv->set, (GObject *)item);
    }

    g_object_unref (item);
  }

  sw_item_view_set_from_set ((SwItemView *)item_view, priv->set);


  sw_cache_save (service,
                 priv->query,
                 priv->params,
                 priv->set);

  sw_set_empty (priv->set);

  rest_xml_node_unref (root);
}
