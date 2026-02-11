evd_stream_throttle_get_property (GObject    *obj,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  EvdStreamThrottle *self;

  self = EVD_STREAM_THROTTLE (obj);

  switch (prop_id)
    {
    case PROP_BANDWIDTH:
      g_value_set_float (value, self->priv->bandwidth / 1024.0);
      break;


    case PROP_LATENCY:
      g_value_set_float (value, self->priv->latency / 1000.0);
      break;

    case PROP_TOTAL:
      g_value_set_uint64 (value, evd_stream_throttle_get_total (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, prop_id, pspec);
      break;
    }
}
