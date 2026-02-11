inf_gtk_browser_store_add_item(InfGtkBrowserStore* store,
                               InfDiscovery* discovery,
                               InfDiscoveryInfo* info,
                               InfXmlConnection* connection,
                               gchar* name)
{
  InfGtkBrowserStorePrivate* priv;
  InfGtkBrowserStoreItem* item;
  InfGtkBrowserStoreItem* cur;
  GtkTreePath* path;
  GtkTreeIter iter;
  guint index;
  InfcBrowser* browser;

  g_assert(
    connection == NULL ||
    inf_gtk_browser_store_find_item_by_connection(store, connection) == NULL
  );

  priv = INF_GTK_BROWSER_STORE_PRIVATE(store);
  item = g_slice_new(InfGtkBrowserStoreItem);
  item->name = name;
  item->discovery = discovery;
  item->info = info;
  item->status = INF_GTK_BROWSER_MODEL_DISCONNECTED;
  if(discovery != NULL && info != NULL)
    item->status = INF_GTK_BROWSER_MODEL_DISCOVERED;
  item->browser = NULL;
  item->missing = NULL;
  item->node_errors = g_hash_table_new_full(
    NULL,
    NULL,
    NULL,
    (GDestroyNotify)g_error_free
  );
  item->requests = NULL;
  item->error = NULL;
  item->next = NULL;

  index = 0;
  for(cur = priv->first_item; cur != NULL; cur = cur->next)
    ++ index;


  if(priv->first_item == NULL)
  {
    priv->first_item = item;
    priv->last_item = item;
  }
  else
  {
    priv->last_item->next = item;
    priv->last_item = item;
  }

  path = gtk_tree_path_new_from_indices(index, -1);
  iter.stamp = priv->stamp;
  iter.user_data = item;
  iter.user_data2 = GUINT_TO_POINTER(0);
  iter.user_data3 = NULL;

  gtk_tree_model_row_inserted(GTK_TREE_MODEL(store), path, &iter);

  if(connection != NULL)
  {
    browser = infc_browser_new(
      priv->io,
      priv->communication_manager,
      connection
    );


    if(infc_browser_get_connection(browser) != NULL)
      inf_gtk_browser_store_item_set_browser(store, item, path, browser);

    g_object_unref(G_OBJECT(browser));
  }

  gtk_tree_path_free(path);
  return item;
}
