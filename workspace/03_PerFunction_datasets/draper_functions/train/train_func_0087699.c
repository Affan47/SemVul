gst_uri_decode_bin_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstURIDecodeBin *dec = GST_URI_DECODE_BIN (object);

  switch (prop_id) {
    case PROP_URI:
      GST_OBJECT_LOCK (dec);
      g_value_set_string (value, dec->uri);
      GST_OBJECT_UNLOCK (dec);
      break;
    case PROP_SOURCE:
      GST_OBJECT_LOCK (dec);
      g_value_set_object (value, dec->source);
      GST_OBJECT_UNLOCK (dec);
      break;
    case PROP_CONNECTION_SPEED:
      GST_OBJECT_LOCK (dec);
      g_value_set_uint64 (value, dec->connection_speed / 1000);
      GST_OBJECT_UNLOCK (dec);
      break;
    case PROP_CAPS:
      GST_OBJECT_LOCK (dec);
      g_value_set_boxed (value, dec->caps);
      GST_OBJECT_UNLOCK (dec);
      break;
    case PROP_SUBTITLE_ENCODING:
      GST_OBJECT_LOCK (dec);
      g_value_set_string (value, dec->encoding);
      GST_OBJECT_UNLOCK (dec);
      break;
    case PROP_BUFFER_SIZE:
      GST_OBJECT_LOCK (dec);
      g_value_set_int (value, dec->buffer_size);
      GST_OBJECT_UNLOCK (dec);
      break;
    case PROP_BUFFER_DURATION:
      GST_OBJECT_LOCK (dec);
      g_value_set_int64 (value, dec->buffer_duration);
      GST_OBJECT_UNLOCK (dec);
      break;
    case PROP_DOWNLOAD:
      g_value_set_boolean (value, dec->download);
      break;
    case PROP_USE_BUFFERING:
      g_value_set_boolean (value, dec->use_buffering);
      break;
    case PROP_EXPOSE_ALL_STREAMS:
      g_value_set_boolean (value, dec->expose_allstreams);
      break;
    case PROP_RING_BUFFER_MAX_SIZE:
      g_value_set_uint64 (value, dec->ring_buffer_max_size);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
