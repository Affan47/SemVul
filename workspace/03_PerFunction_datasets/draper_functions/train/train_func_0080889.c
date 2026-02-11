set_property (GObject *object,
              guint property_id,
              const GValue *value,
              GParamSpec *pspec)
{
  TpTestsTextChannelNull *self = TP_TESTS_TEXT_CHANNEL_NULL (object);

  switch (property_id)
    {
    case PROP_OBJECT_PATH:
      g_free (self->priv->object_path);
      self->priv->object_path = g_value_dup_string (value);
      break;
    case PROP_HANDLE:


      self->priv->handle = g_value_get_uint (value);
      break;
    case PROP_HANDLE_TYPE:
    case PROP_CHANNEL_TYPE:


      break;
    case PROP_CONNECTION:
      self->priv->conn = g_value_get_object (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}
