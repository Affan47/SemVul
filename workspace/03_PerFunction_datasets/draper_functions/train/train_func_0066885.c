copy_packed_simple (guint i_alpha, GstVideoFormat dest_format, guint8 * dest,
    gboolean dest_sdtv, gint dest_width, gint dest_height, gint dest_x,
    gint dest_y, GstVideoFormat src_format, const guint8 * src,
    gboolean src_sdtv, gint src_width, gint src_height, gint src_x, gint src_y,
    gint w, gint h)
{
  gint i;
  gint src_stride, dest_stride;
  gint pixel_stride, row_size;

  src_stride = gst_video_format_get_row_stride (src_format, 0, src_width);
  dest_stride = gst_video_format_get_row_stride (dest_format, 0, dest_width);
  pixel_stride = gst_video_format_get_pixel_stride (dest_format, 0);
  row_size = w * pixel_stride;

  dest = dest + dest_y * dest_stride + dest_x * pixel_stride;
  src = src + src_y * src_stride + src_x * pixel_stride;

  for (i = 0; i < h; i++) {
    memcpy (dest, src, row_size);
    dest += dest_stride;
    src += src_stride;
  }
}
