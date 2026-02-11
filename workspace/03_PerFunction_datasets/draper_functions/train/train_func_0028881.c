gst_rtspsrc_get_position (GstRTSPSrc * src)
{
  GstQuery *query;
  GList *walk;

  query = gst_query_new_position (GST_FORMAT_TIME);

  for (walk = src->streams; walk; walk = g_list_next (walk)) {
    GstRTSPStream *stream = (GstRTSPStream *) walk->data;
    GstFormat fmt;
    gint64 pos;

    if (stream->srcpad) {
      if (gst_pad_query (stream->srcpad, query)) {
        gst_query_parse_position (query, &fmt, &pos);
        GST_DEBUG_OBJECT (src, "retaining position %" GST_TIME_FORMAT,
            GST_TIME_ARGS (pos));
        src->last_pos = pos;
        return;
      }
    }
  }

  src->last_pos = 0;
}
