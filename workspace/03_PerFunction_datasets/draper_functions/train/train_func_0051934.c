gst_ogg_demux_collect_sync_time (GstOggDemux * ogg, GstOggChain * chain)
{
  gint i;
  GstClockTime sync_time = GST_CLOCK_TIME_NONE;

  if (!chain) {
    GST_WARNING_OBJECT (ogg, "No chain!");
    return GST_CLOCK_TIME_NONE;
  }

  for (i = 0; i < chain->streams->len; i++) {
    GstOggPad *pad = g_array_index (chain->streams, GstOggPad *, i);

    if (pad->map.is_sparse)
      continue;

    if (pad->push_sync_time == GST_CLOCK_TIME_NONE) {
      sync_time = GST_CLOCK_TIME_NONE;
      break;
    } else {
      if (sync_time == GST_CLOCK_TIME_NONE)
        sync_time = pad->push_sync_time;
      else
        sync_time = MAX (sync_time, pad->push_sync_time);
    }
  }
  return sync_time;
}
