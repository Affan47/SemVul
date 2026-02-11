gst_flv_demux_handle_seek_push (GstFlvDemux * demux, GstEvent * event)
{
  GstFormat format;

  gst_event_parse_seek (event, NULL, &format, NULL, NULL, NULL, NULL, NULL);

  if (format != GST_FORMAT_TIME) {
    GST_WARNING_OBJECT (demux, "we only support seeking in TIME format");
    gst_event_unref (event);
    return FALSE;
  }


  if (gst_pad_push_event (demux->sinkpad, gst_event_ref (event))) {
    GST_DEBUG_OBJECT (demux, "Upstream successfully seeked");
    gst_event_unref (event);
    return TRUE;
  }

  if (!demux->indexed) {
    guint64 seek_offset = 0;
    gboolean building_index;

    GST_OBJECT_LOCK (demux);

    demux->seeking = TRUE;
    demux->state = FLV_STATE_SEEK;


    if (demux->seek_event)
      gst_event_unref (demux->seek_event);
    demux->seek_event = gst_event_ref (event);


    building_index = demux->building_index;
    if (!building_index) {
      demux->building_index = TRUE;
      if (!demux->file_size
          && !gst_pad_peer_query_duration (demux->sinkpad, GST_FORMAT_BYTES,
              &demux->file_size)) {
        GST_WARNING_OBJECT (demux, "Failed to query upstream file size");
        GST_OBJECT_UNLOCK (demux);
        return FALSE;
      }


      seek_offset = demux->file_size - sizeof (guint32);
      GST_DEBUG_OBJECT (demux,
          "File size obtained, seeking to %" G_GUINT64_FORMAT, seek_offset);
    }
    GST_OBJECT_UNLOCK (demux);

    if (!building_index) {
      GST_INFO_OBJECT (demux, "Seeking to last 4 bytes at %" G_GUINT64_FORMAT,
          seek_offset);
      return flv_demux_seek_to_offset (demux, seek_offset);
    }


    return TRUE;
  }

  return flv_demux_handle_seek_push (demux, event);
}
