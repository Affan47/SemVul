gst_cog_buffer_wrap (GstBuffer * buf, GstVideoFormat format, int width,
    int height)
{
  CogFrame *frame;
  int size;

  size = gst_video_format_get_size (format, width, height);
  if (GST_BUFFER_SIZE (buf) != size) {
    GST_ERROR ("size incorrect, expected %d, got %d", size,
        GST_BUFFER_SIZE (buf));
  }

  switch (format) {
    case GST_VIDEO_FORMAT_I420:
      frame =
          cog_frame_new_from_data_I420 (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_YV12:
      frame =
          cog_frame_new_from_data_YV12 (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_YUY2:
      frame =
          cog_frame_new_from_data_YUY2 (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_UYVY:
      frame =
          cog_frame_new_from_data_UYVY (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_AYUV:
      frame =
          cog_frame_new_from_data_AYUV (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_Y42B:
      frame =
          cog_frame_new_from_data_Y42B (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_Y444:
      frame =
          cog_frame_new_from_data_Y444 (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_v210:
      frame =
          cog_frame_new_from_data_v210 (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_v216:
      frame =
          cog_frame_new_from_data_v216 (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_RGBx:
      frame =
          cog_frame_new_from_data_RGBx (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_BGRx:
      frame =
          cog_frame_new_from_data_BGRx (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_xRGB:
      frame =
          cog_frame_new_from_data_xRGB (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_xBGR:
      frame =
          cog_frame_new_from_data_xBGR (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_RGBA:
      frame =
          cog_frame_new_from_data_RGBA (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_BGRA:
      frame =
          cog_frame_new_from_data_BGRA (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_ARGB:
      frame =
          cog_frame_new_from_data_ARGB (GST_BUFFER_DATA (buf), width, height);
      break;
    case GST_VIDEO_FORMAT_ABGR:
      frame =
          cog_frame_new_from_data_ABGR (GST_BUFFER_DATA (buf), width, height);
      break;
    default:
      g_assert_not_reached ();
      return NULL;
  }
  cog_frame_set_free_callback (frame, gst_cog_frame_free, buf);

  return frame;
}
