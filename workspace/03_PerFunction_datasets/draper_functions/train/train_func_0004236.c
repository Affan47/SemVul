gst_dash_demux_get_video_input_caps (GstDashDemux * demux,
    GstActiveStream * stream)
{
  guint width = 0, height = 0;
  const gchar *mimeType = NULL;
  GstCaps *caps = NULL;

  if (stream == NULL)
    return NULL;


  if (!gst_mpd_client_get_bitstream_switching_flag (stream)) {
    width = gst_mpd_client_get_video_stream_width (stream);
    height = gst_mpd_client_get_video_stream_height (stream);
  }
  mimeType = gst_mpd_client_get_stream_mimeType (stream);
  if (mimeType == NULL)
    return NULL;

  caps = gst_caps_from_string (mimeType);
  if (width > 0 && height > 0) {
    gst_caps_set_simple (caps, "width", G_TYPE_INT, width, "height",
        G_TYPE_INT, height, NULL);
  }

  return caps;
}
