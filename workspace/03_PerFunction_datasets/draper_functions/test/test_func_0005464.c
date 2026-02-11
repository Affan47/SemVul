gst_flups_demux_do_seek (GstFluPSDemux * demux, GstSegment * seeksegment)
{
  gboolean found = FALSE;
  guint64 fscr, offset;
  guint64 scr = GSTTIME_TO_MPEGTIME (seeksegment->position + demux->base_time);


  if (demux->last_scr > demux->last_pts)
    scr = gst_util_uint64_scale (scr, demux->last_scr, demux->last_pts);

  scr = MIN (demux->last_scr, scr);
  scr = MAX (demux->first_scr, scr);
  fscr = scr;

  GST_INFO_OBJECT (demux, "sink segment configured %" GST_SEGMENT_FORMAT
      ", trying to go at SCR: %" G_GUINT64_FORMAT, &demux->sink_segment, scr);

  offset =
      find_offset (demux, scr, demux->first_scr, demux->first_scr_offset,
      demux->last_scr, demux->last_scr_offset, 0);

  if (offset == (guint64) - 1) {
    return FALSE;
  }

  while (found && fscr < scr) {
    offset++;
    found =
        gst_flups_demux_scan_forward_ts (demux, &offset, SCAN_SCR, &fscr, 0);
  }

  while (found && fscr > scr && offset > 0) {
    offset--;
    found =
        gst_flups_demux_scan_backward_ts (demux, &offset, SCAN_SCR, &fscr, 0);
  }

  GST_INFO_OBJECT (demux, "doing seek at offset %" G_GUINT64_FORMAT
      " SCR: %" G_GUINT64_FORMAT " %" GST_TIME_FORMAT,
      offset, fscr, GST_TIME_ARGS (MPEGTIME_TO_GSTTIME (fscr)));

  gst_segment_set_position (&demux->sink_segment, GST_FORMAT_BYTES, offset);

  return TRUE;
}
