theora_enc_init_buffer (th_ycbcr_buffer buf, th_info * info, guint8 * data)
{
  GstVideoFormat format;
  guint i;

  switch (info->pixel_fmt) {
    case TH_PF_444:
      format = GST_VIDEO_FORMAT_Y444;
      break;
    case TH_PF_420:
      format = GST_VIDEO_FORMAT_I420;
      break;
    case TH_PF_422:
      format = GST_VIDEO_FORMAT_Y42B;
      break;
    default:
      g_assert_not_reached ();
  }


  for (i = 0; i < 3; i++) {
    buf[i].width =
        gst_video_format_get_component_width (format, i, info->frame_width);
    buf[i].height =
        gst_video_format_get_component_height (format, i, info->frame_height);

    buf[i].data =
        data + gst_video_format_get_component_offset (format, i,
        info->pic_width, info->pic_height);
    buf[i].stride =
        gst_video_format_get_row_stride (format, i, info->pic_width);
  }
}
