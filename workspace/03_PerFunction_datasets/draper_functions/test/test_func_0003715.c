gst_avi_demux_get_buffer_info (GstAviDemux * avi, GstAviStream * stream,
    guint entry_n, GstClockTime * timestamp, GstClockTime * ts_end,
    guint64 * offset, guint64 * offset_end)
{
  GstAviIndexEntry *entry;

  entry = &stream->index[entry_n];

  if (stream->is_vbr) {

    if (stream->strh->type == GST_RIFF_FCC_auds) {
      if (timestamp)
        *timestamp =
            avi_stream_convert_frames_to_time_unchecked (stream, entry->total);
      if (ts_end) {
        gint size = 1;
        if (G_LIKELY (entry_n + 1 < stream->idx_n))
          size = stream->index[entry_n + 1].total - entry->total;
        *ts_end = avi_stream_convert_frames_to_time_unchecked (stream,
            entry->total + size);
      }
    } else {
      if (timestamp)
        *timestamp =
            avi_stream_convert_frames_to_time_unchecked (stream, entry_n);
      if (ts_end)
        *ts_end = avi_stream_convert_frames_to_time_unchecked (stream,
            entry_n + 1);
    }
  } else if (stream->strh->type == GST_RIFF_FCC_auds) {

    if (timestamp)
      *timestamp =
          avi_stream_convert_bytes_to_time_unchecked (stream, entry->total);
    if (ts_end)
      *ts_end = avi_stream_convert_bytes_to_time_unchecked (stream,
          entry->total + entry->size);
  }
  if (stream->strh->type == GST_RIFF_FCC_vids) {

    if (offset)
      *offset = entry_n;
    if (offset_end)
      *offset_end = entry_n + 1;
  } else {

    if (offset)
      *offset = -1;
    if (offset_end)
      *offset_end = -1;
  }
}
