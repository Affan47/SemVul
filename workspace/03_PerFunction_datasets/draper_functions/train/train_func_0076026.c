gst_audio_test_src_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstAudioTestSrc *src = GST_AUDIO_TEST_SRC (object);

  switch (prop_id) {
    case PROP_SAMPLES_PER_BUFFER:
      g_value_set_int (value, src->samples_per_buffer);
      break;
    case PROP_WAVE:
      g_value_set_enum (value, src->wave);
      break;
    case PROP_FREQ:
      g_value_set_double (value, src->freq);
      break;
    case PROP_VOLUME:
      g_value_set_double (value, src->volume);
      break;
    case PROP_IS_LIVE:
      g_value_set_boolean (value, gst_base_src_is_live (GST_BASE_SRC (src)));
      break;
    case PROP_TIMESTAMP_OFFSET:
      g_value_set_int64 (value, src->timestamp_offset);
      break;
    case PROP_CAN_ACTIVATE_PUSH:
      g_value_set_boolean (value, GST_BASE_SRC (src)->can_activate_push);
      break;
    case PROP_CAN_ACTIVATE_PULL:
      g_value_set_boolean (value, src->can_activate_pull);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
