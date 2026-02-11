gst_bus_add_signal_watch_full (GstBus * bus, gint priority)
{
  g_return_if_fail (GST_IS_BUS (bus));


  GST_OBJECT_LOCK (bus);

  if (bus->priv->num_signal_watchers > 0)
    goto done;


  g_assert (bus->priv->signal_watch_id == 0);

  bus->priv->signal_watch_id =
      gst_bus_add_watch_full_unlocked (bus, priority, gst_bus_async_signal_func,
      NULL, NULL);

  if (G_UNLIKELY (bus->priv->signal_watch_id == 0))
    goto add_failed;

done:

  bus->priv->num_signal_watchers++;

  GST_OBJECT_UNLOCK (bus);
  return;


add_failed:
  {
    g_critical ("Could not add signal watch to bus %s", GST_OBJECT_NAME (bus));
    GST_OBJECT_UNLOCK (bus);
    return;
  }
}
