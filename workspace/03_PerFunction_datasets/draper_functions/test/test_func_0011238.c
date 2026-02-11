setup_ogmvideo_mapper (GstOggStream * pad, ogg_packet * packet)
{
  guint8 *data = packet->packet;
  guint32 fourcc;
  int width, height;
  gint64 time_unit;

  GST_DEBUG ("time unit %d", GST_READ_UINT32_LE (data + 16));
  GST_DEBUG ("samples per unit %d", GST_READ_UINT32_LE (data + 24));

  pad->is_video = TRUE;
  pad->granulerate_n = 10000000;
  time_unit = GST_READ_UINT64_LE (data + 17);
  if (time_unit > G_MAXINT || time_unit < G_MININT) {
    GST_WARNING ("timeunit is out of range");
  }
  pad->granulerate_d = (gint) CLAMP (time_unit, G_MININT, G_MAXINT);

  GST_LOG ("fps = %d/%d = %.3f",
      pad->granulerate_n, pad->granulerate_d,
      (double) pad->granulerate_n / pad->granulerate_d);

  fourcc = GST_READ_UINT32_LE (data + 9);
  width = GST_READ_UINT32_LE (data + 45);
  height = GST_READ_UINT32_LE (data + 49);
  GST_DEBUG ("fourcc: %" GST_FOURCC_FORMAT, GST_FOURCC_ARGS (fourcc));

  pad->caps = gst_riff_create_video_caps (fourcc, NULL, NULL, NULL, NULL, NULL);

  if (pad->caps == NULL) {
    pad->caps = gst_caps_new_simple ("video/x-ogm-unknown",
        "fourcc", GST_TYPE_FOURCC, fourcc,
        "framerate", GST_TYPE_FRACTION, pad->granulerate_n,
        pad->granulerate_d, NULL);
  } else {
    gst_caps_set_simple (pad->caps,
        "framerate", GST_TYPE_FRACTION, pad->granulerate_n,
        pad->granulerate_d,
        "width", G_TYPE_INT, width, "height", G_TYPE_INT, height, NULL);
  }
  GST_DEBUG ("caps: %" GST_PTR_FORMAT, pad->caps);

  pad->n_header_packets = 1;
  pad->frame_size = 1;
  pad->is_ogm = TRUE;

  return TRUE;
}
