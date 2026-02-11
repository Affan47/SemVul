got_status_cb (RestProxyCall *call,
               GError        *error,
               GObject       *weak_object,
               gpointer       userdata)
{
  SwItemView *self = SW_ITEM_VIEW (weak_object);
  SwFacebookItemViewPrivate *priv = GET_PRIVATE (self);
  JsonNode *root;
  SwSet *set;

  if (error)
    {
      g_message ("Error: %s", error->message);

      return;
    }

  root = json_node_from_call (call, NULL);
  if (!root)
    return;

  set = _facebook_status_node_to_set (self, root);

  json_node_free (root);

  if (set != NULL)
    {
      sw_item_view_set_from_set (self, set);


      sw_cache_save (sw_item_view_get_service (self),
                     priv->query,
                     priv->params,
                     set);

      sw_set_unref (set);
    }
}
