gst_encode_bin_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstEncodeBin *ebin = (GstEncodeBin *) object;

  switch (prop_id) {
    case PROP_PROFILE:
      gst_encode_bin_set_profile (ebin,
          (GstEncodingProfile *) g_value_get_object (value));
      break;
    case PROP_QUEUE_BUFFERS_MAX:
      ebin->queue_buffers_max = g_value_get_uint (value);
      break;
    case PROP_QUEUE_BYTES_MAX:
      ebin->queue_bytes_max = g_value_get_uint (value);
      break;
    case PROP_QUEUE_TIME_MAX:
      ebin->queue_time_max = g_value_get_uint64 (value);
      break;
    case PROP_AUDIO_JITTER_TOLERANCE:
      ebin->tolerance = g_value_get_uint64 (value);
      break;
    case PROP_AVOID_REENCODING:
      ebin->avoid_reencoding = g_value_get_boolean (value);
      break;
    case PROP_FLAGS:
      ebin->flags = g_value_get_flags (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
