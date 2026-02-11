gst_base_sink_set_last_buffer_unlocked (GstBaseSink * sink, GstBuffer * buffer)
{
  GstBuffer *old;

  old = sink->priv->last_buffer;
  if (G_LIKELY (old != buffer)) {
    GST_DEBUG_OBJECT (sink, "setting last buffer to %p", buffer);
    if (G_LIKELY (buffer))
      gst_buffer_ref (buffer);
    sink->priv->last_buffer = buffer;
  } else {
    old = NULL;
  }


  if (G_LIKELY (old)) {
    GST_OBJECT_UNLOCK (sink);
    gst_buffer_unref (old);
    GST_OBJECT_LOCK (sink);
  }
}
