gst_patchdetect_set_caps (GstBaseTransform * trans, GstCaps * incaps,
    GstCaps * outcaps)
{
  GstPatchdetect *patchdetect = GST_PATCHDETECT (trans);
  int width, height;
  GstVideoFormat format;
  gboolean ret;

  ret = gst_video_format_parse_caps (incaps, &format, &width, &height);
  if (ret) {
    patchdetect->format = format;
    patchdetect->width = width;
    patchdetect->height = height;
  }

  return ret;
}
