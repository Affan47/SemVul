gst_audio_echo_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstAudioEcho *self = GST_AUDIO_ECHO (object);

  switch (prop_id) {
    case PROP_DELAY:
      g_mutex_lock (&self->lock);
      g_value_set_uint64 (value, self->delay);
      g_mutex_unlock (&self->lock);
      break;
    case PROP_MAX_DELAY:
      g_mutex_lock (&self->lock);
      g_value_set_uint64 (value, self->max_delay);
      g_mutex_unlock (&self->lock);
      break;
    case PROP_INTENSITY:
      g_mutex_lock (&self->lock);
      g_value_set_float (value, self->intensity);
      g_mutex_unlock (&self->lock);
      break;
    case PROP_FEEDBACK:
      g_mutex_lock (&self->lock);
      g_value_set_float (value, self->feedback);
      g_mutex_unlock (&self->lock);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
