gst_video_filter2_set_caps (GstBaseTransform * trans, GstCaps * incaps,
    GstCaps * outcaps)
{
  GstVideoFilter2 *videofilter2;
  gboolean ret;
  int width;
  int height;
  GstVideoFormat format;

  g_return_val_if_fail (GST_IS_VIDEO_FILTER2 (trans), FALSE);
  videofilter2 = GST_VIDEO_FILTER2 (trans);

  ret = gst_video_format_parse_caps (incaps, &format, &width, &height);

  if (ret) {
    videofilter2->format = format;
    videofilter2->width = width;
    videofilter2->height = height;
  }

  return ret;
}
