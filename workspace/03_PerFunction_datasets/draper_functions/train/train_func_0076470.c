gst_clock_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstClock *clock;
  GstClockPrivate *priv;

  clock = GST_CLOCK (object);
  priv = clock->priv;

  switch (prop_id) {
    case PROP_WINDOW_SIZE:
      GST_CLOCK_SLAVE_LOCK (clock);
      g_value_set_int (value, priv->window_size);
      GST_CLOCK_SLAVE_UNLOCK (clock);
      break;
    case PROP_WINDOW_THRESHOLD:
      GST_CLOCK_SLAVE_LOCK (clock);
      g_value_set_int (value, priv->window_threshold);
      GST_CLOCK_SLAVE_UNLOCK (clock);
      break;
    case PROP_TIMEOUT:
      g_value_set_uint64 (value, gst_clock_get_timeout (clock));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
