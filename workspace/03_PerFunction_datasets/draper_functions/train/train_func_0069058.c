fill_yuy2 (GstVideoBoxFill fill_type, guint b_alpha, GstVideoFormat format,
    guint8 * dest, gboolean sdtv, gint width, gint height)
{
  guint8 y, u, v;
  gint i, j;
  gint stride = gst_video_format_get_row_stride (format, 0, width);

  y = (sdtv) ? yuv_sdtv_colors_Y[fill_type] : yuv_hdtv_colors_Y[fill_type];
  u = (sdtv) ? yuv_sdtv_colors_U[fill_type] : yuv_hdtv_colors_U[fill_type];
  v = (sdtv) ? yuv_sdtv_colors_V[fill_type] : yuv_hdtv_colors_V[fill_type];

  width = width + (width % 2);

  if (format == GST_VIDEO_FORMAT_YUY2) {
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j += 2) {
        dest[j * 2 + 0] = y;
        dest[j * 2 + 1] = u;
        dest[j * 2 + 2] = y;
        dest[j * 2 + 3] = v;
      }

      dest += stride;
    }
  } else if (format == GST_VIDEO_FORMAT_YVYU) {
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j += 2) {
        dest[j * 2 + 0] = y;
        dest[j * 2 + 1] = v;
        dest[j * 2 + 2] = y;
        dest[j * 2 + 3] = u;
      }

      dest += stride;
    }
  } else {
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j += 2) {
        dest[j * 2 + 0] = u;
        dest[j * 2 + 1] = y;
        dest[j * 2 + 2] = v;
        dest[j * 2 + 3] = y;
      }

      dest += stride;
    }
  }
}
