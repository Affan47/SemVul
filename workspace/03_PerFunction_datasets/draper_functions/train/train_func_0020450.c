gst_dccp_client_sink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstDCCPClientSink *sink = GST_DCCP_CLIENT_SINK (object);

  switch (prop_id) {
    case PROP_PORT:
      g_value_set_int (value, sink->port);
      break;
    case PROP_SOCK_FD:
      g_value_set_int (value, sink->sock_fd);
      break;
    case PROP_HOST:
      g_value_set_string (value, sink->host);
      break;
    case PROP_CLOSE_FD:
      g_value_set_boolean (value, sink->closed);
      break;
    case PROP_CCID:
      g_value_set_int (value, sink->ccid);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
