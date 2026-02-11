gst_qtdemux_guess_bitrate (GstQTDemux * qtdemux)
{
  QtDemuxStream *stream = NULL;
  gint64 size, duration, sys_bitrate, sum_bitrate = 0;
  gint i;
  guint bitrate;

  if (qtdemux->fragmented)
    return;

  GST_DEBUG_OBJECT (qtdemux, "Looking for streams with unknown bitrate");

  if (!gst_pad_peer_query_duration (qtdemux->sinkpad, GST_FORMAT_BYTES, &size)
      || size <= 0) {
    GST_DEBUG_OBJECT (qtdemux,
        "Size in bytes of the stream not known - bailing");
    return;
  }


  GST_DEBUG_OBJECT (qtdemux, "Total size %" G_GINT64_FORMAT ", header size %u",
      size, qtdemux->header_size);

  if (size < qtdemux->header_size)
    return;

  size = size - qtdemux->header_size;

  if (!gst_qtdemux_get_duration (qtdemux, &duration) ||
      duration == GST_CLOCK_TIME_NONE) {
    GST_DEBUG_OBJECT (qtdemux, "Stream duration not known - bailing");
    return;
  }

  for (i = 0; i < qtdemux->n_streams; i++) {
    switch (qtdemux->streams[i]->subtype) {
      case FOURCC_soun:
      case FOURCC_vide:

        bitrate = 0;
        if (qtdemux->streams[i]->pending_tags) {
          gst_tag_list_get_uint (qtdemux->streams[i]->pending_tags,
              GST_TAG_MAXIMUM_BITRATE, &bitrate);
          gst_tag_list_get_uint (qtdemux->streams[i]->pending_tags,
              GST_TAG_BITRATE, &bitrate);
        }
        if (bitrate)
          sum_bitrate += bitrate;
        else {
          if (stream) {
            GST_DEBUG_OBJECT (qtdemux,
                ">1 stream with unknown bitrate - bailing");
            return;
          } else
            stream = qtdemux->streams[i];
        }

      default:

        break;
    }
  }

  if (!stream) {
    GST_DEBUG_OBJECT (qtdemux, "All stream bitrates are known");
    return;
  }

  sys_bitrate = gst_util_uint64_scale (size, GST_SECOND * 8, duration);

  if (sys_bitrate < sum_bitrate) {


    GST_DEBUG_OBJECT (qtdemux,
        "System bitrate less than sum bitrate - bailing");
    return;
  }

  bitrate = sys_bitrate - sum_bitrate;
  GST_DEBUG_OBJECT (qtdemux, "System bitrate = %" G_GINT64_FORMAT
      ", Stream bitrate = %u", sys_bitrate, bitrate);

  if (!stream->pending_tags)
    stream->pending_tags = gst_tag_list_new_empty ();

  gst_tag_list_add (stream->pending_tags, GST_TAG_MERGE_REPLACE,
      GST_TAG_BITRATE, bitrate, NULL);
}
