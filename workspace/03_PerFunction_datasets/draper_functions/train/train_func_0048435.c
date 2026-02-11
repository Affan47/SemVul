gst_base_src_default_prepare_seek_segment (GstBaseSrc * src, GstEvent * event,
    GstSegment * segment)
{


  GstSeekType start_type, stop_type;
  gint64 start, stop;
  GstSeekFlags flags;
  GstFormat seek_format, dest_format;
  gdouble rate;
  gboolean update;
  gboolean res = TRUE;

  gst_event_parse_seek (event, &rate, &seek_format, &flags,
      &start_type, &start, &stop_type, &stop);
  dest_format = segment->format;

  if (seek_format == dest_format) {
    gst_segment_do_seek (segment, rate, seek_format, flags,
        start_type, start, stop_type, stop, &update);
    return TRUE;
  }

  if (start_type != GST_SEEK_TYPE_NONE) {

    res =
        gst_pad_query_convert (src->srcpad, seek_format, start, dest_format,
        &start);
    start_type = GST_SEEK_TYPE_SET;
  }

  if (res && stop_type != GST_SEEK_TYPE_NONE) {

    res =
        gst_pad_query_convert (src->srcpad, seek_format, stop, dest_format,
        &stop);
    stop_type = GST_SEEK_TYPE_SET;
  }


  gst_segment_do_seek (segment, rate, dest_format, flags, start_type, start,
      stop_type, stop, &update);

  if (!res)
    goto no_format;

  return res;

no_format:
  {
    GST_DEBUG_OBJECT (src, "undefined format given, seek aborted.");
    return FALSE;
  }
}
