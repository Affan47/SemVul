_get_status_updates (SwMySpaceItemView *item_view)
{
  SwMySpaceItemViewPrivate *priv = GET_PRIVATE (item_view);
  GHashTable *params = NULL;
  SwSet *set;
  SwService *service;

  service = sw_item_view_get_service (SW_ITEM_VIEW (item_view));

  if (!sw_service_has_dynamic_cap (service, CREDENTIALS_VALID))
    return;

  set = sw_item_set_new ();

  if (g_str_equal (priv->query, "own"))
    _get_user_status_updates (item_view, set);
  else if (g_str_equal (priv->query, "feed"))
    _get_friends_status_updates (item_view, set);
  else
    g_error (G_STRLOC ": Unexpected query '%s'", priv->query);

  if (params)
    g_hash_table_unref (params);
}
