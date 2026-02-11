mpegts_packetizer_pts_to_ts (MpegTSPacketizer2 * packetizer,
    GstClockTime pts, guint16 pcr_pid)
{
  GstClockTime res = GST_CLOCK_TIME_NONE;
  MpegTSPCR *pcrtable = get_pcr_table (packetizer, pcr_pid);


  if (packetizer->calculate_skew
      && GST_CLOCK_TIME_IS_VALID (pcrtable->base_time)) {
    GST_DEBUG ("pts %" G_GUINT64_FORMAT " base_pcrtime:%" G_GUINT64_FORMAT
        " base_time:%" GST_TIME_FORMAT, pts, pcrtable->base_pcrtime,
        GST_TIME_ARGS (pcrtable->base_time));
    res =
        pts + pcrtable->pcroffset - pcrtable->base_pcrtime +
        pcrtable->base_time + pcrtable->skew;
  } else

  if (packetizer->calculate_offset && pcrtable->first_pcr != -1) {

    if (G_UNLIKELY (pts < pcrtable->first_pcr_ts))
      pts += MPEGTIME_TO_GSTTIME (PTS_DTS_MAX_VALUE);
    res = pts - pcrtable->first_pcr_ts;
  } else
    GST_WARNING ("Not enough information to calculate proper timestamp");

  GST_DEBUG ("Returning timestamp %" GST_TIME_FORMAT " for pts %"
      GST_TIME_FORMAT " pcr_pid:0x%04x", GST_TIME_ARGS (res),
      GST_TIME_ARGS (pts), pcr_pid);
  return res;
}
