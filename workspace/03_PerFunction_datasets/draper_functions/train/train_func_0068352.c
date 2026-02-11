gst_dccp_client_src_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstDCCPClientSrc *src = GST_DCCP_CLIENT_SRC (object);

  switch (prop_id) {
    case PROP_PORT:
      src->port = g_value_get_int (value);
      break;
    case PROP_HOST:
      if (!g_value_get_string (value)) {
        g_warning ("host property cannot be NULL");
        break;
      }
      g_free (src->host);
      src->host = g_strdup (g_value_get_string (value));
      break;
    case PROP_SOCK_FD:
      src->sock_fd = g_value_get_int (value);
      break;
    case PROP_CLOSED:
      src->closed = g_value_get_boolean (value);
      break;
    case PROP_CCID:
      src->ccid = g_value_get_int (value);
      break;
    case PROP_CAPS:
    {
      const GstCaps *new_caps_val = gst_value_get_caps (value);
      GstCaps *new_caps;
      GstCaps *old_caps;

      if (new_caps_val == NULL) {
        new_caps = gst_caps_new_any ();
      } else {
        new_caps = gst_caps_copy (new_caps_val);
      }

      old_caps = src->caps;
      src->caps = new_caps;
      if (old_caps)
        gst_caps_unref (old_caps);
      gst_pad_set_caps (GST_BASE_SRC (src)->srcpad, new_caps);
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
