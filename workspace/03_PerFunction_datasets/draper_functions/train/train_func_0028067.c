gst_ring_buffer_advance (GstRingBuffer * buf, guint advance)
{
  g_return_if_fail (GST_IS_RING_BUFFER (buf));


  g_atomic_int_add (&buf->segdone, advance);


  if (g_atomic_int_compare_and_exchange (&buf->waiting, 1, 0)) {
    GST_OBJECT_LOCK (buf);
    GST_DEBUG_OBJECT (buf, "signal waiter");
    GST_RING_BUFFER_SIGNAL (buf);
    GST_OBJECT_UNLOCK (buf);
  }
}
