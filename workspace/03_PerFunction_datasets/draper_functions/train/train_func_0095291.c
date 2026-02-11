gst_audio_cheb_band_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstAudioChebBand *filter = GST_AUDIO_CHEB_BAND (object);

  switch (prop_id) {
    case PROP_MODE:
      g_mutex_lock (&filter->lock);
      filter->mode = g_value_get_enum (value);
      generate_coefficients (filter, NULL);
      g_mutex_unlock (&filter->lock);
      break;
    case PROP_TYPE:
      g_mutex_lock (&filter->lock);
      filter->type = g_value_get_int (value);
      generate_coefficients (filter, NULL);
      g_mutex_unlock (&filter->lock);
      break;
    case PROP_LOWER_FREQUENCY:
      g_mutex_lock (&filter->lock);
      filter->lower_frequency = g_value_get_float (value);
      generate_coefficients (filter, NULL);
      g_mutex_unlock (&filter->lock);
      break;
    case PROP_UPPER_FREQUENCY:
      g_mutex_lock (&filter->lock);
      filter->upper_frequency = g_value_get_float (value);
      generate_coefficients (filter, NULL);
      g_mutex_unlock (&filter->lock);
      break;
    case PROP_RIPPLE:
      g_mutex_lock (&filter->lock);
      filter->ripple = g_value_get_float (value);
      generate_coefficients (filter, NULL);
      g_mutex_unlock (&filter->lock);
      break;
    case PROP_POLES:
      g_mutex_lock (&filter->lock);
      filter->poles = GST_ROUND_UP_4 (g_value_get_int (value));
      generate_coefficients (filter, NULL);
      g_mutex_unlock (&filter->lock);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
