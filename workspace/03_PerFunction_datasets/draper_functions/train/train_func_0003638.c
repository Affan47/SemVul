fill_planar_yuv (GstVideoBoxFill fill_type, guint b_alpha,
    GstVideoFormat format, guint8 * dest, gboolean sdtv, gint width,
    gint height)
{
  guint8 empty_pixel[3];
  guint8 *destY, *destU, *destV;
  gint strideY, strideUV;
  gint heightY, heightUV;

  if (sdtv) {
    empty_pixel[0] = yuv_sdtv_colors_Y[fill_type];
    empty_pixel[1] = yuv_sdtv_colors_U[fill_type];
    empty_pixel[2] = yuv_sdtv_colors_V[fill_type];
  } else {
    empty_pixel[0] = yuv_hdtv_colors_Y[fill_type];
    empty_pixel[1] = yuv_hdtv_colors_U[fill_type];
    empty_pixel[2] = yuv_hdtv_colors_V[fill_type];
  }

  strideY = gst_video_format_get_row_stride (format, 0, width);
  strideUV = gst_video_format_get_row_stride (format, 1, width);

  destY =
      dest + gst_video_format_get_component_offset (format, 0, width, height);
  destU =
      dest + gst_video_format_get_component_offset (format, 1, width, height);
  destV =
      dest + gst_video_format_get_component_offset (format, 2, width, height);

  heightY = gst_video_format_get_component_height (format, 0, height);
  heightUV = gst_video_format_get_component_height (format, 1, height);

  memset (destY, empty_pixel[0], strideY * heightY);
  memset (destU, empty_pixel[1], strideUV * heightUV);
  memset (destV, empty_pixel[2], strideUV * heightUV);
}
