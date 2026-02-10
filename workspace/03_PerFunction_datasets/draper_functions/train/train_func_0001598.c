gst_multipart_demux_class_init (GstMultipartDemuxClass * klass)
{
  int i;

  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstElementClass *gstelement_class = GST_ELEMENT_CLASS (klass);

  gobject_class->finalize = gst_multipart_demux_finalize;
  gobject_class->set_property = gst_multipart_set_property;
  gobject_class->get_property = gst_multipart_get_property;

  g_object_class_install_property (gobject_class, PROP_BOUNDARY,
      g_param_spec_string ("boundary", "Boundary",
          "The boundary string separating data, automatic if NULL",
          DEFAULT_BOUNDARY,
          G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_AUTOSCAN,
      g_param_spec_boolean ("autoscan", "autoscan",
          "Try to autofind the prefix (deprecated unused, see boundary)",
          DEFAULT_AUTOSCAN, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


  g_object_class_install_property (gobject_class, PROP_SINGLE_STREAM,
      g_param_spec_boolean ("single-stream", "Single Stream",
          "Assume that there is only one stream whose content-type will not change and emit no-more-pads as soon as the first boundary content is parsed, decoded, and pads are linked",
          DEFAULT_SINGLE_STREAM, G_PARAM_READWRITE));


  klass->gstnames = g_hash_table_new (g_str_hash, g_str_equal);
  for (i = 0; gstnames[i].key; i++) {
    g_hash_table_insert (klass->gstnames, (gpointer) gstnames[i].key,
        (gpointer) gstnames[i].val);
  }

  gstelement_class->change_state = gst_multipart_demux_change_state;
}
