gst_query_get_n_allocation_params (GstQuery * query)
{
  GArray *array;
  GstStructure *structure;

  g_return_val_if_fail (GST_QUERY_TYPE (query) == GST_QUERY_ALLOCATION, 0);

  structure = GST_QUERY_STRUCTURE (query);
  array = ensure_array (structure, GST_QUARK (ALLOCATOR),
      sizeof (AllocationParam), (GDestroyNotify) allocation_param_free);

  return array->len;
}
