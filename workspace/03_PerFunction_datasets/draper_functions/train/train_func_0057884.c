gst_decklink_sink_audiosink_query (GstPad * pad, GstObject * parent,
    GstQuery * query)
{
  gboolean res;

  GST_DEBUG_OBJECT (pad, "query: %" GST_PTR_FORMAT, query);

  switch (GST_QUERY_TYPE (query)) {
    default:
      res = gst_pad_query_default (pad, parent, query);
      break;
  }

  return res;
}
