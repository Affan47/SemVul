_sinks_find_sink_by_caps (ClutterGstAutoVideoSink * bin, GstCaps * caps)
{
  GstElement *element = NULL;
  GSList *walk = bin->sinks;

  while (walk) {
    SinkElement *se = (SinkElement *) walk->data;
    if (se) {
      GstCaps *intersect = NULL;

      intersect = gst_caps_intersect (caps, se->caps);
      if (!gst_caps_is_empty (intersect)) {
        element = se->element;
        gst_caps_unref (intersect);
        GST_DEBUG_OBJECT (bin, "found sink %" GST_PTR_FORMAT, element);
        goto beach;
      }
      gst_caps_unref (intersect);
    }
    walk = g_slist_next (walk);
  }

beach:
  return element;
}
