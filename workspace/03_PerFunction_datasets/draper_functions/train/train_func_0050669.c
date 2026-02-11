gst_flups_demux_clear_times (GstFluPSDemux * demux)
{
  gint i, count = demux->found_count;


  for (i = 0; i < count; i++) {
    GstFluPSStream *stream = demux->streams_found[i];

    if (G_LIKELY (stream)) {
      stream->last_seg_start = stream->last_ts = GST_CLOCK_TIME_NONE;
    }
  }
}
