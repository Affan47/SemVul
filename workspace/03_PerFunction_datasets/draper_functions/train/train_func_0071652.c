gst_frei0r_filter_set_caps (GstBaseTransform * trans, GstCaps * incaps,
    GstCaps * outcaps)
{
  GstFrei0rFilter *self = GST_FREI0R_FILTER (trans);
  GstVideoInfo info;

  gst_video_info_init (&info);
  if (!gst_video_info_from_caps (&info, incaps))
    return FALSE;

  self->width = info.width;
  self->height = info.height;

  return TRUE;
}
