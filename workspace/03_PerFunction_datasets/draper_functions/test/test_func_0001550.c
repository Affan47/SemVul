decoder_query_duration_done (GstURIDecodeBin * dec, QueryFold * fold)
{
  GstFormat format;

  gst_query_parse_duration (fold->query, &format, NULL);

  gst_query_set_duration (fold->query, format, fold->max);

  GST_DEBUG ("max duration %" G_GINT64_FORMAT, fold->max);
}
