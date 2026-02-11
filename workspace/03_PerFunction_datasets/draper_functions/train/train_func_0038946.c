gst_adapter_take (GstAdapter * adapter, guint nbytes)
{
  guint8 *data;

  g_return_val_if_fail (GST_IS_ADAPTER (adapter), NULL);
  g_return_val_if_fail (nbytes > 0, NULL);


  if (G_UNLIKELY (nbytes > adapter->size))
    return NULL;

  data = gst_adapter_take_internal (adapter, nbytes);

  gst_adapter_flush_unchecked (adapter, nbytes);

  return data;
}
