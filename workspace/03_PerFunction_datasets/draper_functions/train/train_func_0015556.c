gst_decklink_src_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstDecklinkSrc *decklinksrc;

  decklinksrc = GST_DECKLINK_SRC (object);

  switch (property_id) {
    case PROP_MODE:
      decklinksrc->mode = (GstDecklinkModeEnum) g_value_get_enum (value);
      break;
    case PROP_CONNECTION:
      decklinksrc->connection =
          (GstDecklinkConnectionEnum) g_value_get_enum (value);
      break;
    case PROP_AUDIO_INPUT:
      decklinksrc->audio_connection =
          (GstDecklinkAudioConnectionEnum) g_value_get_enum (value);
      break;
    case PROP_DEVICE_NUMBER:
      decklinksrc->device_number = g_value_get_int (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}
