gst_mpeg_streams_reset_cur_ts (GstMPEGStream * streams[], guint num,
    GstClockTime cur_ts)
{
  guint i;

  for (i = 0; i < num; ++i) {
    if (streams[i] != NULL)
      streams[i]->cur_ts = cur_ts;
  }
}
