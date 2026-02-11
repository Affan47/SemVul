gst_asf_mux_class_init (GstAsfMuxClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  parent_class = g_type_class_peek_parent (klass);

  gobject_class->get_property = gst_asf_mux_get_property;
  gobject_class->set_property = gst_asf_mux_set_property;
  gobject_class->finalize = gst_asf_mux_finalize;

  g_object_class_install_property (gobject_class, PROP_PACKET_SIZE,
      g_param_spec_uint ("packet-size", "Packet size",
          "The ASF packets size (bytes)",
          ASF_MULTIPLE_PAYLOAD_HEADER_SIZE + 1, G_MAXUINT32,
          DEFAULT_PACKET_SIZE,
          G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_PREROLL,
      g_param_spec_uint64 ("preroll", "Preroll",
          "The preroll time (milisecs)",
          0, G_MAXUINT64,
          DEFAULT_PREROLL,
          G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_MERGE_STREAM_TAGS,
      g_param_spec_boolean ("merge-stream-tags", "Merge Stream Tags",
          "If the stream metadata (received as events in the sink) should be "
          "merged to the main file metadata.",
          DEFAULT_MERGE_STREAM_TAGS,
          G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_PADDING,
      g_param_spec_uint64 ("padding", "Padding",
          "Size of the padding object to be added to the end of the header. "
          "If this less than 24 (the smaller size of an ASF object), "
          "no padding is added.",
          0, G_MAXUINT64,
          DEFAULT_PADDING,
          G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_STREAMABLE,
      g_param_spec_boolean ("streamable", "Streamable",
          "If set to true, the output should be as if it is to be streamed "
          "and hence no indexes written or duration written.",
          DEFAULT_STREAMABLE,
          G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS));

  gstelement_class->request_new_pad =
      GST_DEBUG_FUNCPTR (gst_asf_mux_request_new_pad);
  gstelement_class->change_state = GST_DEBUG_FUNCPTR (gst_asf_mux_change_state);

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&src_factory));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&audio_sink_factory));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&video_sink_factory));

  gst_element_class_set_static_metadata (gstelement_class, "ASF muxer",
      "Codec/Muxer",
      "Muxes audio and video into an ASF stream",
      "Thiago Santos <thiagoss@embedded.ufcg.edu.br>");

  GST_DEBUG_CATEGORY_INIT (asfmux_debug, "asfmux", 0, "Muxer for ASF streams");
}
