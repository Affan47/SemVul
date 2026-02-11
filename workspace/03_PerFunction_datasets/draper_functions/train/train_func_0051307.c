gst_tcp_client_sink_stop (GstBaseSink * bsink)
{
  GstTCPClientSink *this = GST_TCP_CLIENT_SINK (bsink);
  GError *err = NULL;

  if (!GST_OBJECT_FLAG_IS_SET (this, GST_TCP_CLIENT_SINK_OPEN))
    return TRUE;

  if (this->socket) {
    GST_DEBUG_OBJECT (this, "closing socket");

    if (!g_socket_close (this->socket, &err)) {
      GST_ERROR_OBJECT (this, "Failed to close socket: %s", err->message);
      g_clear_error (&err);
    }
    g_object_unref (this->socket);
    this->socket = NULL;
  }

  GST_OBJECT_FLAG_UNSET (this, GST_TCP_CLIENT_SINK_OPEN);

  return TRUE;
}
