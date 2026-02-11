gst_query_parse_nth_allocation_meta (GstQuery * query, guint index,
    const GstStructure ** params)
{
  GArray *array;
  GstStructure *structure;
  AllocationMeta *am;

  g_return_val_if_fail (GST_QUERY_TYPE (query) == GST_QUERY_ALLOCATION, 0);

  structure = GST_QUERY_STRUCTURE (query);
  array =
      ensure_array (structure, GST_QUARK (META), sizeof (AllocationMeta),
      (GDestroyNotify) allocation_meta_free);

  g_return_val_if_fail (index < array->len, 0);

  am = &g_array_index (array, AllocationMeta, index);

  if (params)
    *params = am->params;

  return am->api;
}
