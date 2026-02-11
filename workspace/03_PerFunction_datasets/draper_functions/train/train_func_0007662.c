inf_gtk_browser_store_item_request_add(InfGtkBrowserStore* store,
                                       InfGtkBrowserStoreItem* item,
                                       InfcRequest* request)
{
  InfGtkBrowserStoreRequestData* data;

  g_assert(g_slist_find(item->requests, request) == NULL);
  item->requests = g_slist_prepend(item->requests, request);

  data = g_slice_new(InfGtkBrowserStoreRequestData);
  data->store = store;
  data->item = item;

  g_signal_connect_data(
    G_OBJECT(request),
    "failed",
    G_CALLBACK(inf_gtk_browser_store_request_failed_cb),
    data,
    inf_gtk_browser_store_request_data_free,
    0
  );

  g_object_weak_ref(
    G_OBJECT(request),
    inf_gtk_browser_store_request_unrefed_func,
    item
  );
}
