dump_element_stats (GstElement * element)
{
  GstIterator *it;
  gpointer data;

  it = gst_element_iterate_src_pads (element);
  while (gst_iterator_next (it, &data) == GST_ITERATOR_OK) {
    GstPad *pad = GST_PAD (data);
    GstCaps *caps;
    gchar *str;
    GstQuery *query;

    g_print ("stream %s:\n", GST_OBJECT_NAME (pad));

    caps = gst_pad_get_caps (pad);
    str = gst_caps_to_string (caps);
    g_print (" caps: %s\n", str);
    g_free (str);
    gst_caps_unref (caps);

    query = gst_query_new_duration (GST_FORMAT_TIME);
    if (gst_pad_query (pad, query)) {
      gint64 duration;

      gst_query_parse_duration (query, NULL, &duration);

      g_print (" duration: %" GST_TIME_FORMAT "\n", GST_TIME_ARGS (duration));
    }
    gst_query_unref (query);

    gst_object_unref (pad);
  }
  gst_iterator_free (it);
}
