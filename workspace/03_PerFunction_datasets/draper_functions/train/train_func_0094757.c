gst_query_parse_context_type (GstQuery * query, const gchar ** context_type)
{
  GstStructure *structure;
  const GValue *value;

  g_return_val_if_fail (GST_QUERY_TYPE (query) == GST_QUERY_CONTEXT, FALSE);

  structure = GST_QUERY_STRUCTURE (query);

  if (context_type) {
    value = gst_structure_id_get_value (structure, GST_QUARK (CONTEXT_TYPE));
    *context_type = g_value_get_string (value);
  }

  return TRUE;
}
