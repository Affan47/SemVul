gst_flups_demux_handle_seek_push (GstFluPSDemux * demux, GstEvent * event)
{
  gboolean res = FALSE;
  gdouble rate;
  GstFormat format;
  GstSeekFlags flags;
  GstSeekType start_type, stop_type;
  gint64 start, stop;
  gint64 bstart, bstop;
  GstEvent *bevent;

  gst_event_parse_seek (event, &rate, &format, &flags, &start_type, &start,
      &stop_type, &stop);

  GST_DEBUG_OBJECT (demux, "seek event, rate: %f start: %" GST_TIME_FORMAT
      " stop: %" GST_TIME_FORMAT, rate, GST_TIME_ARGS (start),
      GST_TIME_ARGS (stop));

  if (format == GST_FORMAT_BYTES) {
    GST_DEBUG_OBJECT (demux, "seek not supported on format %d", format);
    goto not_supported;
  }

  GST_DEBUG_OBJECT (demux, "seek - trying directly upstream first");


  (void) gst_event_ref (event);
  if ((res = gst_pad_push_event (demux->sinkpad, event)))
    goto done;

  if (format != GST_FORMAT_TIME) {

    GST_DEBUG_OBJECT (demux, "seek not supported on format %d", format);
    goto not_supported;
  }


  if (demux->scr_rate_n == G_MAXUINT64 || demux->scr_rate_d == G_MAXUINT64) {
    GST_DEBUG_OBJECT (demux, "seek not possible, no scr_rate");
    goto not_supported;
  }

  GST_DEBUG_OBJECT (demux, "try with scr_rate interpolation");

  bstart = GSTTIME_TO_BYTES ((guint64) start);
  bstop = GSTTIME_TO_BYTES ((guint64) stop);

  GST_DEBUG_OBJECT (demux, "in bytes bstart %" G_GINT64_FORMAT " bstop %"
      G_GINT64_FORMAT, bstart, bstop);
  bevent = gst_event_new_seek (rate, GST_FORMAT_BYTES, flags, start_type,
      bstart, stop_type, bstop);

  res = gst_pad_push_event (demux->sinkpad, bevent);

done:
  gst_event_unref (event);
  return res;

not_supported:
  {
    gst_event_unref (event);

    return FALSE;
  }
}
