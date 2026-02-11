gst_stream_info_class_init (GstStreamInfoClass * klass)
{
  GObjectClass *gobject_klass;

  gobject_klass = (GObjectClass *) klass;

  parent_class = g_type_class_peek_parent (klass);

  gobject_klass->set_property = gst_stream_info_set_property;
  gobject_klass->get_property = gst_stream_info_get_property;

  g_object_class_install_property (gobject_klass, ARG_PAD,
      g_param_spec_object ("object", "object",
          "Source Pad or object of the stream", GST_TYPE_OBJECT,
          G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_klass, ARG_TYPE,
      g_param_spec_enum ("type", "Type", "Type of the stream",
          GST_TYPE_STREAM_TYPE, GST_STREAM_TYPE_UNKNOWN,
          G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_klass, ARG_DECODER,
      g_param_spec_string ("decoder", "Decoder",
          "The decoder used to decode the stream", NULL,
          G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_klass, ARG_MUTE,
      g_param_spec_boolean ("mute", "Mute", "Mute or unmute this stream", FALSE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_klass, ARG_CAPS,
      g_param_spec_boxed ("caps", "Capabilities",
          "Capabilities (or type) of this stream", GST_TYPE_CAPS,
          G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_klass, ARG_LANG_CODE,
      g_param_spec_string ("language-code", "Language code",
          "Language code for this stream, conforming to ISO-639-1", NULL,
          G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_klass, ARG_CODEC,
      g_param_spec_string ("codec", "Codec", "Codec used to encode the stream",
          NULL, G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));

  gst_stream_info_signals[SIGNAL_MUTED] =
      g_signal_new ("muted", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
      G_STRUCT_OFFSET (GstStreamInfoClass, muted), NULL, NULL,
      gst_marshal_VOID__BOOLEAN, G_TYPE_NONE, 1, G_TYPE_BOOLEAN);

  gobject_klass->dispose = gst_stream_info_dispose;

  GST_DEBUG_CATEGORY_INIT (gst_streaminfo_debug, "streaminfo", 0,
      "Playbin Stream Info");
}
