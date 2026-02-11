gst_live_adder_query_duration (GstLiveAdder * adder, GstQuery * query)
{
  GstFormat format;
  gint64 max;
  gboolean res;


  gst_query_parse_duration (query, &format, NULL);

  res = gst_live_adder_query_pos_dur (adder, format, FALSE, &max);

  if (res) {

    gst_query_set_duration (query, format, max);
  }

  return res;
}
