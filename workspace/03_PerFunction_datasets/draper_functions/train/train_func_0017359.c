gst_bus_set_sync_handler (GstBus * bus, GstBusSyncHandler func,
    gpointer user_data, GDestroyNotify notify)
{
  GDestroyNotify old_notify;

  g_return_if_fail (GST_IS_BUS (bus));

  GST_OBJECT_LOCK (bus);


  if (func != NULL && bus->priv->sync_handler != NULL)
    goto no_replace;

  if ((old_notify = bus->priv->sync_handler_notify)) {
    gpointer old_data = bus->priv->sync_handler_data;

    bus->priv->sync_handler_data = NULL;
    bus->priv->sync_handler_notify = NULL;
    GST_OBJECT_UNLOCK (bus);

    old_notify (old_data);

    GST_OBJECT_LOCK (bus);
  }
  bus->priv->sync_handler = func;
  bus->priv->sync_handler_data = user_data;
  bus->priv->sync_handler_notify = notify;
  GST_OBJECT_UNLOCK (bus);

  return;

no_replace:
  {
    GST_OBJECT_UNLOCK (bus);
    g_warning ("cannot replace existing sync handler");
    return;
  }
}
