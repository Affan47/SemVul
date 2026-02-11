psmux_stream_add_data (PsMuxStream * stream, GstBuffer * buffer,
    gint64 pts, gint64 dts, gboolean keyunit)
{
  PsMuxStreamBuffer *packet;

  g_return_if_fail (stream != NULL);

  packet = g_slice_new (PsMuxStreamBuffer);
  packet->buf = buffer;

  if (!gst_buffer_map (packet->buf, &packet->map, GST_MAP_READ)) {
    GST_ERROR ("Failed to map buffer for reading");
    gst_buffer_unref (packet->buf);
    g_slice_free (PsMuxStreamBuffer, packet);
    return;
  }

  packet->keyunit = keyunit;
  packet->pts = pts;
  packet->dts = dts;

  if (stream->bytes_avail == 0)
    stream->last_pts = pts;

  stream->bytes_avail += packet->map.size;

  stream->buffers = g_list_append (stream->buffers, packet);

}
