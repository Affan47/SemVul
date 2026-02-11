gst_avdtp_sink_render (GstBaseSink * basesink, GstBuffer * buffer)
{
  GstFlowReturn flow_ret = GST_FLOW_OK;
  GstAvdtpSink *self = GST_AVDTP_SINK (basesink);
  GstMapInfo map;
  ssize_t ret;
  int fd;

  if (!gst_buffer_map (buffer, &map, GST_MAP_READ))
    return GST_FLOW_ERROR;


  g_assert (!(g_io_channel_get_flags (self->conn.stream) & G_IO_FLAG_NONBLOCK));


  fd = g_io_channel_unix_get_fd (self->conn.stream);
  ret = write (fd, map.data, map.size);
  if (ret < 0) {

    GST_ERROR_OBJECT (self, "Error writing to socket: %s", g_strerror (errno));
    flow_ret = GST_FLOW_ERROR;
  }

  gst_buffer_unmap (buffer, &map);
  return flow_ret;
}
