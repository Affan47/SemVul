gst_bus_have_pending (GstBus * bus)
{
  gboolean result;

  g_return_val_if_fail (GST_IS_BUS (bus), FALSE);


  result = gst_atomic_queue_length (bus->priv->queue) != 0;

  return result;
}
