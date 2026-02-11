gst_audio_delay_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstBtAudioDelay *filter = GSTBT_AUDIO_DELAY (object);

  switch (prop_id) {
    case PROP_DRYWET:
      filter->drywet = g_value_get_uint (value);
      break;
    case PROP_DELAYTIME:
      filter->delaytime = g_value_get_uint (value);
      break;
    case PROP_FEEDBACK:
      filter->feedback = g_value_get_uint (value);
      break;

    case PROP_BPM:
    case PROP_TPB:
    case PROP_STPT:
      GST_WARNING("use gstbt_tempo_change_tempo()");
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
