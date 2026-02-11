gst_decode_bin_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstDecodeBin *dbin;

  dbin = GST_DECODE_BIN (object);
  switch (prop_id) {
    case PROP_CAPS:
      g_value_take_boxed (value, gst_decode_bin_get_caps (dbin));
      break;
    case PROP_SUBTITLE_ENCODING:
      g_value_take_string (value, gst_decode_bin_get_subs_encoding (dbin));
      break;
    case PROP_SINK_CAPS:
      g_value_take_boxed (value, gst_decode_bin_get_sink_caps (dbin));
      break;
    case PROP_USE_BUFFERING:
      g_value_set_boolean (value, dbin->use_buffering);
      break;
    case PROP_LOW_PERCENT:
      g_value_set_int (value, dbin->low_percent);
      break;
    case PROP_HIGH_PERCENT:
      g_value_set_int (value, dbin->high_percent);
      break;
    case PROP_MAX_SIZE_BYTES:
      g_value_set_uint (value, dbin->max_size_bytes);
      break;
    case PROP_MAX_SIZE_BUFFERS:
      g_value_set_uint (value, dbin->max_size_buffers);
      break;
    case PROP_MAX_SIZE_TIME:
      g_value_set_uint64 (value, dbin->max_size_time);
      break;
    case PROP_POST_STREAM_TOPOLOGY:
      g_value_set_boolean (value, dbin->post_stream_topology);
      break;
    case PROP_EXPOSE_ALL_STREAMS:
      g_value_set_boolean (value, dbin->expose_allstreams);
      break;
    case PROP_CONNECTION_SPEED:
      GST_OBJECT_LOCK (dbin);
      g_value_set_uint64 (value, dbin->connection_speed / 1000);
      GST_OBJECT_UNLOCK (dbin);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
