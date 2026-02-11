gst_ring_buffer_set_callback (GstRingBuffer * buf, GstRingBufferCallback cb,
    gpointer user_data)
{
  g_return_if_fail (GST_IS_RING_BUFFER (buf));

  GST_OBJECT_LOCK (buf);
  buf->callback = cb;
  buf->cb_data = user_data;
  GST_OBJECT_UNLOCK (buf);
}
