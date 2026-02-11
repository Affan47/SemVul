gst_theora_parse_class_init (GstTheoraParseClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstElementClass *gstelement_class = GST_ELEMENT_CLASS (klass);

  gobject_class->dispose = theora_parse_dispose;
  gobject_class->get_property = theora_parse_get_property;
  gobject_class->set_property = theora_parse_set_property;


  g_object_class_install_property (gobject_class, PROP_SYNCHRONIZATION_POINTS,
      g_param_spec_value_array ("synchronization-points",
          "Synchronization points",
          "An array of (granuletime, buffertime) pairs",
          g_param_spec_uint64 ("time", "Time",
              "Time (either granuletime or buffertime)", 0, G_MAXUINT64, 0,
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS),
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  gstelement_class->change_state = theora_parse_change_state;

  GST_DEBUG_CATEGORY_INIT (theoraparse_debug, "theoraparse", 0,
      "Theora parser");
}
