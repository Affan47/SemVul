gst_mss_demux_reconfigure_stream (GstMssDemuxStream * stream)
{
  GstMssDemux *mssdemux = stream->parent;
  guint64 new_bitrate;

  new_bitrate =
      mssdemux->bitrate_limit *
      gst_download_rate_get_current_rate (&stream->download_rate);
  if (mssdemux->connection_speed) {
    new_bitrate = MIN (mssdemux->connection_speed, new_bitrate);
  }

  GST_DEBUG_OBJECT (mssdemux,
      "Current stream %s download bitrate %" G_GUINT64_FORMAT,
      GST_PAD_NAME (stream->pad), new_bitrate);

  if (gst_mss_stream_select_bitrate (stream->manifest_stream, new_bitrate)) {
    GstEvent *capsevent;
    GstCaps *caps;
    caps = gst_mss_stream_get_caps (stream->manifest_stream);

    if (stream->caps)
      gst_caps_unref (stream->caps);
    stream->caps = create_mss_caps (stream, caps);
    gst_caps_unref (caps);

    GST_DEBUG_OBJECT (mssdemux,
        "Stream %s changed bitrate to %" G_GUINT64_FORMAT " caps: %"
        GST_PTR_FORMAT, GST_PAD_NAME (stream->pad),
        gst_mss_stream_get_current_bitrate (stream->manifest_stream), caps);

    capsevent = gst_event_new_caps (stream->caps);
    gst_mss_demux_stream_store_object (stream,
        GST_MINI_OBJECT_CAST (capsevent));
  }
}
