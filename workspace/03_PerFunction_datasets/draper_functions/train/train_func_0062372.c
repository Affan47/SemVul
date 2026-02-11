gst_oss_mixer_element_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstOssMixerElement *this = GST_OSS_MIXER_ELEMENT (object);

  switch (prop_id) {
    case PROP_DEVICE:
      g_value_set_string (value, this->device);
      break;
    case PROP_DEVICE_NAME:
      if (this->mixer) {
        g_value_set_string (value, this->mixer->cardname);
      } else {
        g_value_set_string (value, NULL);
      }
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
