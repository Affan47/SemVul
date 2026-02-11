mpegts_packetizer_push (MpegTSPacketizer2 * packetizer, GstBuffer * buffer)
{
  if (G_UNLIKELY (packetizer->empty)) {
    packetizer->empty = FALSE;
    packetizer->offset = GST_BUFFER_OFFSET (buffer);
  }

  GST_DEBUG ("Pushing %" G_GSIZE_FORMAT " byte from offset %"
      G_GUINT64_FORMAT, gst_buffer_get_size (buffer),
      GST_BUFFER_OFFSET (buffer));
  gst_adapter_push (packetizer->adapter, buffer);

  if (GST_CLOCK_TIME_IS_VALID (GST_BUFFER_TIMESTAMP (buffer)))
    packetizer->priv->last_in_time = GST_BUFFER_TIMESTAMP (buffer);
}
