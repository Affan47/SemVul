gst_audio_echo_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstAudioEcho *self = GST_AUDIO_ECHO (object);

  switch (prop_id) {
    case PROP_DELAY:
      GST_BASE_TRANSFORM_LOCK (self);
      g_value_set_uint64 (value, self->delay);
      GST_BASE_TRANSFORM_UNLOCK (self);
      break;
    case PROP_MAX_DELAY:
      GST_BASE_TRANSFORM_LOCK (self);
      g_value_set_uint64 (value, self->max_delay);
      GST_BASE_TRANSFORM_UNLOCK (self);
      break;
    case PROP_INTENSITY:
      GST_BASE_TRANSFORM_LOCK (self);
      g_value_set_float (value, self->intensity);
      GST_BASE_TRANSFORM_UNLOCK (self);
      break;
    case PROP_FEEDBACK:
      GST_BASE_TRANSFORM_LOCK (self);
      g_value_set_float (value, self->feedback);
      GST_BASE_TRANSFORM_UNLOCK (self);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
