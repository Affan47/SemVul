gst_query_add_scheduling_mode (GstQuery * query, GstPadMode mode)
{
  GstStructure *structure;
  GArray *array;

  g_return_if_fail (GST_QUERY_TYPE (query) == GST_QUERY_SCHEDULING);
  g_return_if_fail (gst_query_is_writable (query));

  structure = GST_QUERY_STRUCTURE (query);
  array =
      ensure_array (structure, GST_QUARK (MODES), sizeof (GstPadMode), NULL);

  g_array_append_val (array, mode);
}
