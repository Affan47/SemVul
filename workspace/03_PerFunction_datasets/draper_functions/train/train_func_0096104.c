graph_proxy_destroy(
  graph_proxy_handle graph)
{
  ASSERT(list_empty(&graph_ptr->monitors));

  if (graph_ptr->active)
  {
    cdbus_unregister_object_signal_hooks(
      cdbus_g_dbus_connection,
      graph_ptr->service,
      graph_ptr->object,
      JACKDBUS_IFACE_PATCHBAY);
  }

  free(graph_ptr->object);
  free(graph_ptr->service);
  free(graph_ptr);
}
