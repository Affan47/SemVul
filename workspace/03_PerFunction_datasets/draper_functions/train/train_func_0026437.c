gst_query_parse_n_formats (GstQuery * query, guint * n_formats)
{
  GstStructure *structure;

  g_return_if_fail (GST_QUERY_TYPE (query) == GST_QUERY_FORMATS);

  if (n_formats) {
    const GValue *list;

    structure = GST_QUERY_STRUCTURE (query);
    list = gst_structure_get_value (structure, "formats");
    if (list == NULL)
      *n_formats = 0;
    else
      *n_formats = gst_value_list_get_size (list);
  }
}
