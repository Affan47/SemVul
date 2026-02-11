tp_base_call_channel_set_property (GObject *object,
    guint property_id,
    const GValue *value,
    GParamSpec *pspec)
{
  TpBaseCallChannel *self = TP_BASE_CALL_CHANNEL (object);

  switch (property_id)
    {
      case PROP_INITIAL_AUDIO:
        self->priv->initial_audio = g_value_get_boolean (value);
        break;
      case PROP_INITIAL_VIDEO:
        self->priv->initial_video = g_value_get_boolean (value);
        break;
      case PROP_INITIAL_AUDIO_NAME:
        self->priv->initial_audio_name = g_value_dup_string (value);
        break;
      case PROP_INITIAL_VIDEO_NAME:
        self->priv->initial_video_name = g_value_dup_string (value);
        break;
      case PROP_INITIAL_TRANSPORT:
        self->priv->initial_transport = g_value_get_uint (value);
        break;
      case PROP_MUTABLE_CONTENTS:
        self->priv->mutable_contents = g_value_get_boolean (value);
        break;
      case PROP_INITIAL_TONES:
        self->priv->initial_tones = g_value_dup_string (value);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
  }
}
