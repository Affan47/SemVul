gst_trigger_control_source_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstTriggerControlSource *self = GST_TRIGGER_CONTROL_SOURCE (object);

  switch (prop_id) {
    case PROP_TOLERANCE:
      GST_TIMED_VALUE_CONTROL_SOURCE_LOCK (self);
      self->priv->tolerance = g_value_get_int64 (value);
      GST_TIMED_VALUE_CONTROL_SOURCE_UNLOCK (self);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
