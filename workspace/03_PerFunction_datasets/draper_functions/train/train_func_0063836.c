gst_video_balance_init (GstVideoBalance * videobalance)
{
  const gchar *channels[4] = { "HUE", "SATURATION",
    "BRIGHTNESS", "CONTRAST"
  };
  gint i;


  videobalance->contrast = DEFAULT_PROP_CONTRAST;
  videobalance->brightness = DEFAULT_PROP_BRIGHTNESS;
  videobalance->hue = DEFAULT_PROP_HUE;
  videobalance->saturation = DEFAULT_PROP_SATURATION;

  videobalance->tableu[0] = g_new (guint8, 256 * 256 * 2);
  for (i = 0; i < 256; i++) {
    videobalance->tableu[i] =
        videobalance->tableu[0] + i * 256 * sizeof (guint8);
    videobalance->tablev[i] =
        videobalance->tableu[0] + 256 * 256 * sizeof (guint8) +
        i * 256 * sizeof (guint8);
  }

  gst_video_balance_update_properties (videobalance);


  for (i = 0; i < G_N_ELEMENTS (channels); i++) {
    GstColorBalanceChannel *channel;

    channel = g_object_new (GST_TYPE_COLOR_BALANCE_CHANNEL, NULL);
    channel->label = g_strdup (channels[i]);
    channel->min_value = -1000;
    channel->max_value = 1000;

    videobalance->channels = g_list_append (videobalance->channels, channel);
  }
}
