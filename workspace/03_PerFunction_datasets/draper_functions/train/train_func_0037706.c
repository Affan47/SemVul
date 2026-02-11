fill_rgb32 (GstVideoBoxFill fill_type, guint b_alpha,
    GstVideoFrame * frame, gboolean sdtv)
{
  guint32 empty_pixel;
  gint p[4];
  guint8 *dest;
  guint stride;
  gint width, height;

  width = GST_VIDEO_FRAME_WIDTH (frame);
  height = GST_VIDEO_FRAME_HEIGHT (frame);

  dest = GST_VIDEO_FRAME_PLANE_DATA (frame, 0);
  stride = GST_VIDEO_FRAME_PLANE_STRIDE (frame, 0);

  p[0] = GST_VIDEO_FRAME_COMP_OFFSET (frame, 3);
  p[1] = GST_VIDEO_FRAME_COMP_OFFSET (frame, 0);
  p[2] = GST_VIDEO_FRAME_COMP_OFFSET (frame, 1);
  p[3] = GST_VIDEO_FRAME_COMP_OFFSET (frame, 2);

  b_alpha = CLAMP (b_alpha, 0, 255);

  empty_pixel = GUINT32_FROM_LE ((b_alpha << (p[0] * 8)) |
      (rgb_colors_R[fill_type] << (p[1] * 8)) |
      (rgb_colors_G[fill_type] << (p[2] * 8)) |
      (rgb_colors_B[fill_type] << (p[3] * 8)));

  if (stride == width * 4) {
    video_box_orc_splat_u32 ((guint32 *) dest, empty_pixel, width * height);
  } else if (height) {
    for (; height; --height) {
      video_box_orc_splat_u32 ((guint32 *) dest, empty_pixel, width);
      dest += stride;
    }
  }
}
