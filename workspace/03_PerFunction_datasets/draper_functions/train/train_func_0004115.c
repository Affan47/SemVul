gst_bin_dispose (GObject * object)
{
  GstBin *bin = GST_BIN_CAST (object);
  GstBus **child_bus_p = &bin->child_bus;
  GstClock **provided_clock_p = &bin->provided_clock;
  GstElement **clock_provider_p = &bin->clock_provider;

  GST_CAT_DEBUG_OBJECT (GST_CAT_REFCOUNTING, object, "dispose");

  GST_OBJECT_LOCK (object);
  gst_object_replace ((GstObject **) child_bus_p, NULL);
  gst_object_replace ((GstObject **) provided_clock_p, NULL);
  gst_object_replace ((GstObject **) clock_provider_p, NULL);
  bin_remove_messages (bin, NULL, GST_MESSAGE_ANY);
  GST_OBJECT_UNLOCK (object);

  while (bin->children) {
    gst_bin_remove (bin, GST_ELEMENT_CAST (bin->children->data));
  }
  if (G_UNLIKELY (bin->children != NULL)) {
    g_critical ("could not remove elements from bin '%s'",
        GST_STR_NULL (GST_OBJECT_NAME (object)));
  }

  g_list_free_full (bin->priv->contexts, (GDestroyNotify) gst_context_unref);

  G_OBJECT_CLASS (parent_class)->dispose (object);
}
