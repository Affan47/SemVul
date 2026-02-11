gst_deinterlace_method_setup_impl (GstDeinterlaceMethod * self,
    GstVideoFormat format, gint width, gint height)
{
  gint i;
  GstDeinterlaceMethodClass *klass = GST_DEINTERLACE_METHOD_GET_CLASS (self);

  self->format = format;
  self->frame_width = width;
  self->frame_height = height;

  self->deinterlace_frame = NULL;

  if (format == GST_VIDEO_FORMAT_UNKNOWN)
    return;

  for (i = 0; i < 4; i++) {
    self->width[i] = gst_video_format_get_component_width (format, i, width);
    self->height[i] = gst_video_format_get_component_height (format, i, height);
    self->offset[i] =
        gst_video_format_get_component_offset (format, i, width, height);
    self->row_stride[i] = gst_video_format_get_row_stride (format, i, width);
    self->pixel_stride[i] = gst_video_format_get_pixel_stride (format, i);
  }

  switch (format) {
    case GST_VIDEO_FORMAT_YUY2:
      self->deinterlace_frame = klass->deinterlace_frame_yuy2;
      break;
    case GST_VIDEO_FORMAT_YVYU:
      self->deinterlace_frame = klass->deinterlace_frame_yvyu;
      break;
    case GST_VIDEO_FORMAT_UYVY:
      self->deinterlace_frame = klass->deinterlace_frame_uyvy;
      break;
    case GST_VIDEO_FORMAT_I420:
      self->deinterlace_frame = klass->deinterlace_frame_i420;
      break;
    case GST_VIDEO_FORMAT_YV12:
      self->deinterlace_frame = klass->deinterlace_frame_yv12;
      break;
    case GST_VIDEO_FORMAT_Y444:
      self->deinterlace_frame = klass->deinterlace_frame_y444;
      break;
    case GST_VIDEO_FORMAT_Y42B:
      self->deinterlace_frame = klass->deinterlace_frame_y42b;
      break;
    case GST_VIDEO_FORMAT_Y41B:
      self->deinterlace_frame = klass->deinterlace_frame_y41b;
      break;
    case GST_VIDEO_FORMAT_AYUV:
      self->deinterlace_frame = klass->deinterlace_frame_ayuv;
      break;
    case GST_VIDEO_FORMAT_NV12:
      self->deinterlace_frame = klass->deinterlace_frame_nv12;
      break;
    case GST_VIDEO_FORMAT_NV21:
      self->deinterlace_frame = klass->deinterlace_frame_nv21;
      break;
    case GST_VIDEO_FORMAT_ARGB:
    case GST_VIDEO_FORMAT_xRGB:
      self->deinterlace_frame = klass->deinterlace_frame_argb;
      break;
    case GST_VIDEO_FORMAT_ABGR:
    case GST_VIDEO_FORMAT_xBGR:
      self->deinterlace_frame = klass->deinterlace_frame_abgr;
      break;
    case GST_VIDEO_FORMAT_RGBA:
    case GST_VIDEO_FORMAT_RGBx:
      self->deinterlace_frame = klass->deinterlace_frame_rgba;
      break;
    case GST_VIDEO_FORMAT_BGRA:
    case GST_VIDEO_FORMAT_BGRx:
      self->deinterlace_frame = klass->deinterlace_frame_bgra;
      break;
    case GST_VIDEO_FORMAT_RGB:
      self->deinterlace_frame = klass->deinterlace_frame_rgb;
      break;
    case GST_VIDEO_FORMAT_BGR:
      self->deinterlace_frame = klass->deinterlace_frame_bgr;
      break;
    default:
      self->deinterlace_frame = NULL;
      break;
  }
}
