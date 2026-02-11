gst_identity_get_property (GObject * object, guint prop_id, GValue * value,
    GParamSpec * pspec)
{
  GstIdentity *identity;

  identity = GST_IDENTITY (object);

  switch (prop_id) {
    case PROP_SLEEP_TIME:
      g_value_set_uint (value, identity->sleep_time);
      break;
    case PROP_ERROR_AFTER:
      g_value_set_int (value, identity->error_after);
      break;
    case PROP_DROP_PROBABILITY:
      g_value_set_float (value, identity->drop_probability);
      break;
    case PROP_DATARATE:
      g_value_set_int (value, identity->datarate);
      break;
    case PROP_SILENT:
      g_value_set_boolean (value, identity->silent);
      break;
    case PROP_SINGLE_SEGMENT:
      g_value_set_boolean (value, identity->single_segment);
      break;
    case PROP_DUMP:
      g_value_set_boolean (value, identity->dump);
      break;
    case PROP_LAST_MESSAGE:
      GST_OBJECT_LOCK (identity);
      g_value_set_string (value, identity->last_message);
      GST_OBJECT_UNLOCK (identity);
      break;
    case PROP_SYNC:
      g_value_set_boolean (value, identity->sync);
      break;
    case PROP_CHECK_PERFECT:
      g_value_set_boolean (value, identity->check_perfect);
      break;
    case PROP_CHECK_IMPERFECT_TIMESTAMP:
      g_value_set_boolean (value, identity->check_imperfect_timestamp);
      break;
    case PROP_CHECK_IMPERFECT_OFFSET:
      g_value_set_boolean (value, identity->check_imperfect_offset);
      break;
    case PROP_SIGNAL_HANDOFFS:
      g_value_set_boolean (value, identity->signal_handoffs);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
