gst_bz2enc_class_init (GstBz2encClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstElementClass *gstelement_class = GST_ELEMENT_CLASS (klass);

  gobject_class->finalize = gst_bz2enc_finalize;
  gobject_class->set_property = gst_bz2enc_set_property;
  gobject_class->get_property = gst_bz2enc_get_property;

  g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_BLOCK_SIZE,
      g_param_spec_uint ("block-size", "Block size", "Block size",
          1, 9, DEFAULT_BLOCK_SIZE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_BUFFER_SIZE,
      g_param_spec_uint ("buffer-size", "Buffer size", "Buffer size",
          1, G_MAXUINT, DEFAULT_BUFFER_SIZE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sink_template));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&src_template));
  gst_element_class_set_static_metadata (gstelement_class, "BZ2 encoder",
      "Codec/Encoder", "Compresses streams",
      "Lutz Mueller <lutz@users.sourceforge.net>");

  GST_DEBUG_CATEGORY_INIT (bz2enc_debug, "bz2enc", 0, "BZ2 compressor");
}
