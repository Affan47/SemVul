gst_tcp_client_sink_render (GstBaseSink * bsink, GstBuffer * buf)
{
  GstTCPClientSink *sink;
  GstMapInfo map;
  gsize written = 0;
  gssize rret;
  GError *err = NULL;

  sink = GST_TCP_CLIENT_SINK (bsink);

  g_return_val_if_fail (GST_OBJECT_FLAG_IS_SET (sink, GST_TCP_CLIENT_SINK_OPEN),
      GST_FLOW_FLUSHING);

  gst_buffer_map (buf, &map, GST_MAP_READ);
  GST_LOG_OBJECT (sink, "writing %" G_GSIZE_FORMAT " bytes for buffer data",
      map.size);


  while (written < map.size) {
    rret =
        g_socket_send (sink->socket, (gchar *) map.data + written,
        map.size - written, sink->cancellable, &err);
    if (rret < 0)
      goto write_error;
    written += rret;
  }
  gst_buffer_unmap (buf, &map);

  sink->data_written += written;

  return GST_FLOW_OK;


write_error:
  {
    GstFlowReturn ret;

    if (g_error_matches (err, G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
      ret = GST_FLOW_FLUSHING;
      GST_DEBUG_OBJECT (sink, "Cancelled reading from socket");
    } else {
      GST_ELEMENT_ERROR (sink, RESOURCE, WRITE,
          (_("Error while sending data to \"%s:%d\"."), sink->host, sink->port),
          ("Only %" G_GSIZE_FORMAT " of %" G_GSIZE_FORMAT " bytes written: %s",
              written, map.size, err->message));
      ret = GST_FLOW_ERROR;
    }
    gst_buffer_unmap (buf, &map);
    g_clear_error (&err);
    return ret;
  }
}
