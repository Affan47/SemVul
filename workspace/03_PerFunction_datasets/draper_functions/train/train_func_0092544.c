_sinks_discover (ClutterGstAutoVideoSink * bin)
{
  GstCaps *caps = gst_caps_new_empty ();
  GList *factories, *item;

  factories = gst_registry_feature_filter (gst_registry_get (),
      (GstPluginFeatureFilter) _factory_filter, FALSE, bin);
  factories = g_list_sort (factories, (GCompareFunc) _factories_compare_ranks);

  for (item = factories; item != NULL; item = item->next) {
    GstElementFactory *f = GST_ELEMENT_FACTORY (item->data);
    GstElement *el;
    SinkElement *se;

    if ((el = _create_element_with_pretty_name (bin, f))) {
      GST_DEBUG_OBJECT (bin, "Testing %s",
          gst_plugin_feature_get_name (GST_PLUGIN_FEATURE (f)));


      if (!_is_clutter_sink (el)) {
        gst_object_unref (el);
        continue;
      }
      se = _sink_element_create (el);
      if (se) {
        GstCaps *caps_union = gst_caps_merge (caps, gst_caps_ref (se->caps));
        caps = caps_union;
        bin->sinks = g_slist_append (bin->sinks, se);
        GST_DEBUG_OBJECT (bin, "Added %s with caps %" GST_PTR_FORMAT,
            gst_plugin_feature_get_name (GST_PLUGIN_FEATURE (f)), se->caps);
      } else {
        gst_object_unref (el);
      }
    }
  }

  if (!gst_caps_is_empty (caps)) {
    gst_caps_replace (&bin->video_caps, caps);
    GST_DEBUG_OBJECT (bin, "Supported caps %" GST_PTR_FORMAT, bin->video_caps);
  }
  gst_caps_unref (caps);
}
