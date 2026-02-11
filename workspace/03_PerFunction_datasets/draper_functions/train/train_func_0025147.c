gst_query_parse_uri_redirection (GstQuery * query, gchar ** uri)
{
  GstStructure *structure;

  g_return_if_fail (GST_QUERY_TYPE (query) == GST_QUERY_URI);

  structure = GST_QUERY_STRUCTURE (query);
  if (uri) {
    if (!gst_structure_id_get (structure, GST_QUARK (URI_REDIRECTION),
            G_TYPE_STRING, uri, NULL))
      *uri = NULL;
  }
}
