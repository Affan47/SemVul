gst_clock_overlay_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstClockOverlay *overlay = GST_CLOCK_OVERLAY (object);

  GST_OBJECT_LOCK (overlay);
  switch (prop_id) {
    case PROP_TIMEFORMAT:
      g_free (overlay->format);
      overlay->format = g_value_dup_string (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
  GST_OBJECT_UNLOCK (overlay);
}
