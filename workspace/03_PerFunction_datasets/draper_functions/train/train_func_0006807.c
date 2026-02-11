gst_collect_pads_class_init (GstCollectPadsClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  g_type_class_add_private (klass, sizeof (GstCollectPadsPrivate));

  GST_DEBUG_CATEGORY_INIT (collect_pads_debug, "collectpads", 0,
      "GstCollectPads");

  gobject_class->finalize = gst_collect_pads_finalize;
}
