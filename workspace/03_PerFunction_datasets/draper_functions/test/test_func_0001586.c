gst_oss4_sink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstOss4Sink *oss = GST_OSS4_SINK (object);

  switch (prop_id) {
    case PROP_DEVICE:
      GST_OBJECT_LOCK (oss);
      g_value_set_string (value, oss->device);
      GST_OBJECT_UNLOCK (oss);
      break;
    case PROP_DEVICE_NAME:
      GST_OBJECT_LOCK (oss);
      if (oss->fd == -1 && oss->device != NULL) {

        if (gst_oss4_sink_open (GST_AUDIO_SINK (oss), TRUE)) {
          g_value_set_string (value, oss->device_name);
          gst_oss4_sink_close (GST_AUDIO_SINK (oss));
        } else {
          gchar *name = NULL;

          gst_oss4_property_probe_find_device_name_nofd (GST_OBJECT (oss),
              oss->device, &name);
          g_value_set_string (value, name);
          g_free (name);
        }
      } else {
        g_value_set_string (value, oss->device_name);
      }
      GST_OBJECT_UNLOCK (oss);
      break;
    case PROP_VOLUME:
      g_value_set_double (value, gst_oss4_sink_get_volume (oss));
      break;
    case PROP_MUTE:
      g_value_set_boolean (value, gst_oss4_sink_get_mute (oss));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
