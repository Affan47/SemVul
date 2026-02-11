gst_base_sink_set_last_buffer_enabled (GstBaseSink * sink, gboolean enabled)
{
  g_return_if_fail (GST_IS_BASE_SINK (sink));


  if (g_atomic_int_compare_and_exchange (&sink->priv->enable_last_buffer,
          !enabled, enabled) && !enabled) {
    GST_OBJECT_LOCK (sink);
    gst_base_sink_set_last_buffer_unlocked (sink, NULL);
    GST_OBJECT_UNLOCK (sink);
  }
}
