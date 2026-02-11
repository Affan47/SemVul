gst_play_bin_update_cached_duration (GstPlayBin * playbin)
{
  const GstFormat formats[] =
      { GST_FORMAT_TIME, GST_FORMAT_BYTES, GST_FORMAT_DEFAULT };
  gboolean ret;
  GstQuery *query;
  gint i;

  GST_DEBUG_OBJECT (playbin, "Updating cached durations before group switch");
  for (i = 0; i < G_N_ELEMENTS (formats); i++) {
    query = gst_query_new_duration (formats[i]);
    ret =
        GST_ELEMENT_CLASS (parent_class)->query (GST_ELEMENT_CAST (playbin),
        query);
    gst_play_bin_update_cached_duration_from_query (playbin, ret, query);
    gst_query_unref (query);
  }
}
