gst_adapter_flush (GstAdapter * adapter, guint flush)
{
  g_return_if_fail (GST_IS_ADAPTER (adapter));
  g_return_if_fail (flush <= adapter->size);


  if (G_UNLIKELY (flush == 0))
    return;

  gst_adapter_flush_unchecked (adapter, flush);
}
