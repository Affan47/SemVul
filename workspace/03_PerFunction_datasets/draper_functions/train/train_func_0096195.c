gst_dccp_client_sink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstDCCPClientSink *sink = GST_DCCP_CLIENT_SINK (object);

  switch (prop_id) {
    case PROP_PORT:
      sink->port = g_value_get_int (value);
      break;
    case PROP_SOCK_FD:
      sink->sock_fd = g_value_get_int (value);
      break;
    case PROP_HOST:
      if (!g_value_get_string (value)) {
        g_warning ("host property cannot be NULL");
        break;
      }
      g_free (sink->host);
      sink->host = g_strdup (g_value_get_string (value));
      break;
    case PROP_CLOSE_FD:
      sink->closed = g_value_get_boolean (value);
      break;
    case PROP_CCID:
      sink->ccid = g_value_get_int (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
