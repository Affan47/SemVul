gst_spectrum_class_init (GstSpectrumClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstBaseTransformClass *trans_class = GST_BASE_TRANSFORM_CLASS (klass);
  GstAudioFilterClass *filter_class = GST_AUDIO_FILTER_CLASS (klass);

  gobject_class->set_property = gst_spectrum_set_property;
  gobject_class->get_property = gst_spectrum_get_property;
  gobject_class->finalize = gst_spectrum_finalize;

  trans_class->start = GST_DEBUG_FUNCPTR (gst_spectrum_start);
  trans_class->stop = GST_DEBUG_FUNCPTR (gst_spectrum_stop);
  trans_class->transform_ip = GST_DEBUG_FUNCPTR (gst_spectrum_transform_ip);
  trans_class->passthrough_on_same_caps = TRUE;

  filter_class->setup = GST_DEBUG_FUNCPTR (gst_spectrum_setup);


  g_object_class_install_property (gobject_class, PROP_MESSAGE,
      g_param_spec_boolean ("message", "Message",
          "Whether to post a 'spectrum' element message on the bus for each "
          "passed interval (deprecated, use post-messages)", DEFAULT_MESSAGE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


  g_object_class_install_property (gobject_class, PROP_POST_MESSAGES,
      g_param_spec_boolean ("post-messages", "Post Messages",
          "Whether to post a 'spectrum' element message on the bus for each "
          "passed interval", DEFAULT_POST_MESSAGES,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_MESSAGE_MAGNITUDE,
      g_param_spec_boolean ("message-magnitude", "Magnitude",
          "Whether to add a 'magnitude' field to the structure of any "
          "'spectrum' element messages posted on the bus",
          DEFAULT_MESSAGE_MAGNITUDE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_MESSAGE_PHASE,
      g_param_spec_boolean ("message-phase", "Phase",
          "Whether to add a 'phase' field to the structure of any "
          "'spectrum' element messages posted on the bus",
          DEFAULT_MESSAGE_PHASE, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_INTERVAL,
      g_param_spec_uint64 ("interval", "Interval",
          "Interval of time between message posts (in nanoseconds)",
          1, G_MAXUINT64, DEFAULT_INTERVAL,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_BANDS,
      g_param_spec_uint ("bands", "Bands", "Number of frequency bands",
          0, G_MAXUINT, DEFAULT_BANDS,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_THRESHOLD,
      g_param_spec_int ("threshold", "Threshold",
          "dB threshold for result. All lower values will be set to this",
          G_MININT, 0, DEFAULT_THRESHOLD,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


  g_object_class_install_property (gobject_class, PROP_MULTI_CHANNEL,
      g_param_spec_boolean ("multi-channel", "Multichannel results",
          "Send separate results for each channel",
          DEFAULT_MULTI_CHANNEL, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  GST_DEBUG_CATEGORY_INIT (gst_spectrum_debug, "spectrum", 0,
      "audio spectrum analyser element");
}
