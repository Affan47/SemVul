inf_gtk_browser_store_dispose(GObject* object)
{
  InfGtkBrowserStore* store;
  InfGtkBrowserStorePrivate* priv;
  GSList* item;

  store = INF_GTK_BROWSER_STORE(object);
  priv = INF_GTK_BROWSER_STORE_PRIVATE(store);

  while(priv->first_item != NULL)
    inf_gtk_browser_store_remove_item(store, priv->first_item);
  g_assert(priv->last_item == NULL);

  for(item = priv->discoveries; item != NULL; item = g_slist_next(item))
  {
    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(item->data),
      G_CALLBACK(inf_gtk_browser_store_discovered_cb),
      store
    );

    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(item->data),
      G_CALLBACK(inf_gtk_browser_store_undiscovered_cb),
      store
    );

    g_object_unref(G_OBJECT(item->data));
  }

  g_slist_free(priv->discoveries);
  priv->discoveries = NULL;

  if(priv->communication_manager != NULL)
  {
    g_object_unref(priv->communication_manager);
    priv->communication_manager = NULL;
  }

  if(priv->io != NULL)
  {
    g_object_unref(G_OBJECT(priv->io));
    priv->io = NULL;
  }

  G_OBJECT_CLASS(parent_class)->dispose(object);
}
