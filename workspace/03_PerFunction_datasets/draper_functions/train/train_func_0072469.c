gst_smpte_alpha_set_info (GstVideoFilter * vfilter, GstCaps * incaps,
    GstVideoInfo * in_info, GstCaps * outcaps, GstVideoInfo * out_info)
{
  GstSMPTEAlpha *smpte = GST_SMPTE_ALPHA (vfilter);
  gboolean ret;
  gint width, height;

  smpte->process = NULL;

  smpte->in_format = GST_VIDEO_INFO_FORMAT (in_info);
  smpte->out_format = GST_VIDEO_INFO_FORMAT (out_info);
  smpte->width = width = GST_VIDEO_INFO_WIDTH (out_info);
  smpte->height = height = GST_VIDEO_INFO_HEIGHT (out_info);


  GST_OBJECT_LOCK (smpte);
  ret =
      gst_smpte_alpha_update_mask (smpte, smpte->type, smpte->invert,
      smpte->depth, width, height);
  GST_OBJECT_UNLOCK (smpte);
  if (!ret)
    goto mask_failed;

  switch (smpte->out_format) {
    case GST_VIDEO_FORMAT_AYUV:
      switch (smpte->in_format) {
        case GST_VIDEO_FORMAT_AYUV:
          smpte->process = gst_smpte_alpha_process_ayuv_ayuv;
          break;
        case GST_VIDEO_FORMAT_I420:
          smpte->process = gst_smpte_alpha_process_i420_ayuv;
          break;
        default:
          break;
      }
      break;
    case GST_VIDEO_FORMAT_ARGB:
      switch (smpte->in_format) {
        case GST_VIDEO_FORMAT_ARGB:
          smpte->process = gst_smpte_alpha_process_argb_argb;
          break;
        default:
          break;
      }
      break;
    case GST_VIDEO_FORMAT_RGBA:
      switch (smpte->in_format) {
        case GST_VIDEO_FORMAT_RGBA:
          smpte->process = gst_smpte_alpha_process_rgba_rgba;
          break;
        default:
          break;
      }
      break;
    case GST_VIDEO_FORMAT_ABGR:
      switch (smpte->in_format) {
        case GST_VIDEO_FORMAT_ABGR:
          smpte->process = gst_smpte_alpha_process_abgr_abgr;
          break;
        default:
          break;
      }
      break;
    case GST_VIDEO_FORMAT_BGRA:
      switch (smpte->in_format) {
        case GST_VIDEO_FORMAT_BGRA:
          smpte->process = gst_smpte_alpha_process_bgra_bgra;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

  return ret;


mask_failed:
  {
    GST_ERROR_OBJECT (smpte, "failed creating the mask");
    return FALSE;
  }
}
