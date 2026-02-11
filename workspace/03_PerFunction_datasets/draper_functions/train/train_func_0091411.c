gst_navigation_query_get_type (GstQuery * query)
{
  const GstStructure *s;
  const gchar *q_type;

  if (query == NULL || GST_QUERY_TYPE (query) != GST_QUERY_CUSTOM)
    return GST_NAVIGATION_QUERY_INVALID;

  s = gst_query_get_structure (query);
  if (s == NULL || !gst_structure_has_name (s, GST_NAVIGATION_QUERY_NAME))
    return GST_NAVIGATION_QUERY_INVALID;

  q_type = gst_structure_get_string (s, "type");
  if (q_type == NULL)
    return GST_NAVIGATION_QUERY_INVALID;

  if (g_str_equal (q_type, "commands"))
    return GST_NAVIGATION_QUERY_COMMANDS;
  else if (g_str_equal (q_type, "angles"))
    return GST_NAVIGATION_QUERY_ANGLES;

  return GST_NAVIGATION_QUERY_INVALID;
}
