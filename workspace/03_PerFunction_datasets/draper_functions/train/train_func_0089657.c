evd_stream_throttle_set_property (GObject      *obj,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec)
{
  EvdStreamThrottle *self;

  self = EVD_STREAM_THROTTLE (obj);

  switch (prop_id)
    {
    case PROP_BANDWIDTH:
      self->priv->bandwidth = (gsize) (g_value_get_float (value) * 1024.0);
      break;


    case PROP_LATENCY:
      self->priv->latency = (gulong) (g_value_get_float (value) * 1000.0);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, prop_id, pspec);
      break;
    }
}
