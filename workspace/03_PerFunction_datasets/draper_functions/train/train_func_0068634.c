gst_goom_class_init (GstGoomClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  parent_class = g_type_class_peek_parent (klass);

  gobject_class->finalize = gst_goom_finalize;

  gstelement_class->change_state = GST_DEBUG_FUNCPTR (gst_goom_change_state);

  gst_element_class_set_static_metadata (gstelement_class,
      "GOOM: what a GOOM! 2k1 edition", "Visualization",
      "Takes frames of data and outputs video frames using the GOOM 2k1 filter",
      "Wim Taymans <wim@fluendo.com>");
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sink_template));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&src_template));

  GST_DEBUG_CATEGORY_INIT (goom_debug, "goom", 0, "goom visualisation element");
}
