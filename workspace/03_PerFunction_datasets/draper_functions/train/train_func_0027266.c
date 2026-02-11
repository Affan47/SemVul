gst_play_sink_find_property_sinks (GstPlaySink * playsink, GstElement * obj,
    const gchar * name, GType expected_type)
{
  GstElement *result = NULL;
  GstIterator *it;

  if (element_has_property (obj, name, expected_type)) {
    result = obj;
  } else if (GST_IS_BIN (obj)) {
    gboolean found;
    GValue item = { 0, };
    FindPropertyHelper helper = { name, expected_type, TRUE };

    it = gst_bin_iterate_recurse (GST_BIN_CAST (obj));
    found = gst_iterator_find_custom (it,
        (GCompareFunc) find_property, &item, &helper);
    gst_iterator_free (it);
    if (found) {
      result = g_value_get_object (&item);

      g_value_unset (&item);
    }
  }
  return result;
}
