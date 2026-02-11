gst_multi_handle_sink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstMultiHandleSink *multihandlesink;

  multihandlesink = GST_MULTI_HANDLE_SINK (object);

  switch (prop_id) {
    case PROP_BUFFERS_MAX:
      multihandlesink->units_max = g_value_get_int (value);
      break;
    case PROP_BUFFERS_SOFT_MAX:
      multihandlesink->units_soft_max = g_value_get_int (value);
      break;
    case PROP_TIME_MIN:
      multihandlesink->time_min = g_value_get_int64 (value);
      break;
    case PROP_BYTES_MIN:
      multihandlesink->bytes_min = g_value_get_int (value);
      break;
    case PROP_BUFFERS_MIN:
      multihandlesink->buffers_min = g_value_get_int (value);
      break;
    case PROP_UNIT_FORMAT:
      multihandlesink->unit_format = g_value_get_enum (value);
      break;
    case PROP_UNITS_MAX:
      multihandlesink->units_max = g_value_get_int64 (value);
      break;
    case PROP_UNITS_SOFT_MAX:
      multihandlesink->units_soft_max = g_value_get_int64 (value);
      break;
    case PROP_RECOVER_POLICY:
      multihandlesink->recover_policy = g_value_get_enum (value);
      break;
    case PROP_TIMEOUT:
      multihandlesink->timeout = g_value_get_uint64 (value);
      break;
    case PROP_SYNC_METHOD:
      multihandlesink->def_sync_method = g_value_get_enum (value);
      break;
    case PROP_BURST_FORMAT:
      multihandlesink->def_burst_format = g_value_get_enum (value);
      break;
    case PROP_BURST_VALUE:
      multihandlesink->def_burst_value = g_value_get_uint64 (value);
      break;
    case PROP_QOS_DSCP:
      multihandlesink->qos_dscp = g_value_get_int (value);
      gst_multi_handle_sink_setup_dscp (multihandlesink);
      break;

    case PROP_RESEND_STREAMHEADER:
      multihandlesink->resend_streamheader = g_value_get_boolean (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
