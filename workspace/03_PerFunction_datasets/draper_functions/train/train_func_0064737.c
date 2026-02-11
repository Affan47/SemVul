translate_incoming_duration_query (GnlObject * object, GstQuery * query)
{
  GstFormat format;
  gint64 cur;

  gst_query_parse_duration (query, &format, &cur);
  if (G_UNLIKELY (format != GST_FORMAT_TIME)) {
    GST_WARNING_OBJECT (object,
        "We can only handle duration queries in GST_FORMAT_TIME");
    return FALSE;
  }

  gst_query_set_duration (query, GST_FORMAT_TIME, object->duration);

  return TRUE;
}
