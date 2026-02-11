gst_jpeg_dec_class_init (GstJpegDecClass * klass)
{
  GstElementClass *gstelement_class;
  GObjectClass *gobject_class;

  gstelement_class = (GstElementClass *) klass;
  gobject_class = (GObjectClass *) klass;

  parent_class = g_type_class_peek_parent (klass);

  gobject_class->finalize = gst_jpeg_dec_finalize;
  gobject_class->set_property = gst_jpeg_dec_set_property;
  gobject_class->get_property = gst_jpeg_dec_get_property;

  g_object_class_install_property (gobject_class, PROP_IDCT_METHOD,
      g_param_spec_enum ("idct-method", "IDCT Method",
          "The IDCT algorithm to use", GST_TYPE_IDCT_METHOD,
          JPEG_DEFAULT_IDCT_METHOD,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


  g_object_class_install_property (gobject_class, PROP_MAX_ERRORS,
      g_param_spec_int ("max-errors", "Maximum Consecutive Decoding Errors",
          "Error out after receiving N consecutive decoding errors "
          "(-1 = never fail, 0 = automatic, 1 = fail on first error)",
          -1, G_MAXINT, JPEG_DEFAULT_MAX_ERRORS,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  gstelement_class->change_state =
      GST_DEBUG_FUNCPTR (gst_jpeg_dec_change_state);

  GST_DEBUG_CATEGORY_INIT (jpeg_dec_debug, "jpegdec", 0, "JPEG decoder");
  GST_DEBUG_CATEGORY_GET (GST_CAT_PERFORMANCE, "GST_PERFORMANCE");
}
