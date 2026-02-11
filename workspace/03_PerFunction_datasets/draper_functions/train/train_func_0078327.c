gst_decklink_sink_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstDecklinkSink *decklinksink;

  g_return_if_fail (GST_IS_DECKLINK_SINK (object));
  decklinksink = GST_DECKLINK_SINK (object);

  switch (property_id) {
    case PROP_MODE:
      decklinksink->mode = (GstDecklinkModeEnum) g_value_get_enum (value);
      break;
    case PROP_DEVICE_NUMBER:
      decklinksink->device_number = g_value_get_int (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}
