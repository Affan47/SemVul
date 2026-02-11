gst_base_sink_get_last_sample (GstBaseSink * sink)
{
  GstSample *res = NULL;

  g_return_val_if_fail (GST_IS_BASE_SINK (sink), NULL);

  GST_OBJECT_LOCK (sink);
  if (sink->priv->last_buffer) {
    res = gst_sample_new (sink->priv->last_buffer,
        sink->priv->last_caps, &sink->segment, NULL);
  }
  GST_OBJECT_UNLOCK (sink);

  return res;
}
