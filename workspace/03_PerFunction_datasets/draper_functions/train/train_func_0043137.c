gst_color_effects_set_info (GstVideoFilter * vfilter, GstCaps * incaps,
    GstVideoInfo * in_info, GstCaps * outcaps, GstVideoInfo * out_info)
{
  GstColorEffects *filter = GST_COLOR_EFFECTS (vfilter);

  GST_DEBUG_OBJECT (filter,
      "in %" GST_PTR_FORMAT " out %" GST_PTR_FORMAT, incaps, outcaps);

  filter->process = NULL;

  filter->format = GST_VIDEO_INFO_FORMAT (in_info);
  filter->width = GST_VIDEO_INFO_WIDTH (in_info);
  filter->height = GST_VIDEO_INFO_HEIGHT (in_info);

  GST_OBJECT_LOCK (filter);

  switch (filter->format) {
    case GST_VIDEO_FORMAT_AYUV:
      filter->process = gst_color_effects_transform_ayuv;
      break;
    case GST_VIDEO_FORMAT_ARGB:
    case GST_VIDEO_FORMAT_ABGR:
    case GST_VIDEO_FORMAT_RGBA:
    case GST_VIDEO_FORMAT_BGRA:
    case GST_VIDEO_FORMAT_xRGB:
    case GST_VIDEO_FORMAT_xBGR:
    case GST_VIDEO_FORMAT_RGBx:
    case GST_VIDEO_FORMAT_BGRx:
    case GST_VIDEO_FORMAT_RGB:
    case GST_VIDEO_FORMAT_BGR:
      filter->process = gst_color_effects_transform_rgb;
      break;
    default:
      break;
  }

  GST_OBJECT_UNLOCK (filter);

  return filter->process != NULL;
}
