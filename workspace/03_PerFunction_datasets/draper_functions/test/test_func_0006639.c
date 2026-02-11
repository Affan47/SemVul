tp_tests_stream_tube_channel_set_property (GObject *object,
    guint property_id,
    const GValue *value,
    GParamSpec *pspec)
{
  TpTestsStreamTubeChannel *self = (TpTestsStreamTubeChannel *) object;

  switch (property_id)
    {
      case PROP_SUPPORTED_SOCKET_TYPES:
        self->priv->supported_socket_types = g_value_dup_boxed (value);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}
