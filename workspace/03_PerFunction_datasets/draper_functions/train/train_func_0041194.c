gst_mss_demux_class_init (GstMssDemuxClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&gst_mss_demux_sink_template));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&gst_mss_demux_videosrc_template));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&gst_mss_demux_audiosrc_template));
  gst_element_class_set_static_metadata (gstelement_class,
      "Smooth Streaming demuxer", "Demuxer",
      "Parse and demultiplex a Smooth Streaming manifest into audio and video "
      "streams", "Thiago Santos <thiago.sousa.santos@collabora.com>");

  gobject_class->dispose = gst_mss_demux_dispose;
  gobject_class->set_property = gst_mss_demux_set_property;
  gobject_class->get_property = gst_mss_demux_get_property;

  g_object_class_install_property (gobject_class, PROP_CONNECTION_SPEED,
      g_param_spec_uint ("connection-speed", "Connection Speed",
          "Network connection speed in kbps (0 = unknown)",
          0, G_MAXUINT / 1000, DEFAULT_CONNECTION_SPEED,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_MAX_QUEUE_SIZE_BUFFERS,
      g_param_spec_uint ("max-queue-size-buffers", "Max queue size in buffers",
          "Maximum buffers that can be stored in each internal stream queue "
          "(0 = infinite)", 0, G_MAXUINT, DEFAULT_MAX_QUEUE_SIZE_BUFFERS,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_BITRATE_LIMIT,
      g_param_spec_float ("bitrate-limit",
          "Bitrate limit in %",
          "Limit of the available bitrate to use when switching to alternates.",
          0, 1, DEFAULT_BITRATE_LIMIT,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  gstelement_class->change_state =
      GST_DEBUG_FUNCPTR (gst_mss_demux_change_state);

  GST_DEBUG_CATEGORY_INIT (mssdemux_debug, "mssdemux", 0, "mssdemux plugin");
}
