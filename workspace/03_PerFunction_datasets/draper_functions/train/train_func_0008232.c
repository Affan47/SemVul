gst_mms_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstMMS *mmssrc = GST_MMS (object);

  switch (prop_id) {
    case PROP_LOCATION:
      gst_mms_uri_set_uri (GST_URI_HANDLER (mmssrc),
          g_value_get_string (value), NULL);
      break;
    case PROP_CONNECTION_SPEED:
      GST_OBJECT_LOCK (mmssrc);
      mmssrc->connection_speed = g_value_get_uint64 (value) * 1000;
      GST_OBJECT_UNLOCK (mmssrc);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
