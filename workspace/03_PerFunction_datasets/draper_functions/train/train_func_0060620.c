gst_flups_demux_scan_forward_ts (GstFluPSDemux * demux, guint64 * pos,
    SCAN_MODE mode, guint64 * rts, gint limit)
{
  GstFlowReturn ret = GST_FLOW_OK;
  GstBuffer *buffer;
  guint64 offset = *pos;
  gboolean found = FALSE;
  guint64 ts = 0;
  guint scan_sz = (mode == SCAN_SCR ? SCAN_SCR_SZ : SCAN_PTS_SZ);
  guint cursor, to_read = BLOCK_SZ;
  guint end_scan;
  GstMapInfo map;

  do {
    if (offset + scan_sz > demux->sink_segment.stop)
      return FALSE;

    if (limit && offset > *pos + limit)
      return FALSE;

    if (offset + to_read > demux->sink_segment.stop)
      to_read = demux->sink_segment.stop - offset;


    buffer = NULL;
    ret = gst_pad_pull_range (demux->sinkpad, offset, to_read, &buffer);
    if (G_UNLIKELY (ret != GST_FLOW_OK))
      return FALSE;
    gst_buffer_map (buffer, &map, GST_MAP_READ);


    if (G_UNLIKELY (map.size <= scan_sz)) {
      gst_buffer_unmap (buffer, &map);
      gst_buffer_unref (buffer);
      return FALSE;
    }

    end_scan = map.size - scan_sz;


    for (cursor = 0; !found && cursor <= end_scan; cursor++) {
      found = gst_flups_demux_scan_ts (demux, map.data + cursor, mode, &ts);
    }


    gst_buffer_unmap (buffer, &map);
    gst_buffer_unref (buffer);

    if (found) {
      *rts = ts;
      *pos = offset + cursor - 1;
    } else {
      offset += cursor;
    }
  } while (!found && offset < demux->sink_segment.stop);

  return found;
}
