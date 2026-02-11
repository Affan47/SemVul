gst_ogg_demux_collect_chain_info (GstOggDemux * ogg, GstOggChain * chain)
{
  gboolean res = TRUE;

  chain->total_time = GST_CLOCK_TIME_NONE;
  GST_DEBUG_OBJECT (ogg, "trying to collect chain info");


  chain->segment_start = gst_ogg_demux_collect_start_time (ogg, chain);

  if (chain->segment_start == G_MAXUINT64) {

    res = FALSE;
  } else if (chain->segment_stop != GST_CLOCK_TIME_NONE) {

    chain->total_time = chain->segment_stop - chain->segment_start;
  }

  GST_DEBUG ("total time %" G_GUINT64_FORMAT, chain->total_time);

  GST_DEBUG_OBJECT (ogg, "return %d", res);

  return res;
}
