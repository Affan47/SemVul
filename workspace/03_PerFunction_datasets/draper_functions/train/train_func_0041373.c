gst_video_balance_packed_rgb (GstVideoBalance * videobalance,
    GstVideoFrame * frame)
{
  gint i, j, height;
  gint width, stride, row_wrap;
  gint pixel_stride;
  guint8 *data;
  gint offsets[3];
  gint r, g, b;
  gint y, u, v;
  gint u_tmp, v_tmp;
  guint8 *tabley = videobalance->tabley;
  guint8 **tableu = videobalance->tableu;
  guint8 **tablev = videobalance->tablev;

  width = GST_VIDEO_FRAME_WIDTH (frame);
  height = GST_VIDEO_FRAME_HEIGHT (frame);

  offsets[0] = GST_VIDEO_FRAME_COMP_OFFSET (frame, 0);
  offsets[1] = GST_VIDEO_FRAME_COMP_OFFSET (frame, 1);
  offsets[2] = GST_VIDEO_FRAME_COMP_OFFSET (frame, 2);

  data = GST_VIDEO_FRAME_PLANE_DATA (frame, 0);
  stride = GST_VIDEO_FRAME_PLANE_STRIDE (frame, 0);

  pixel_stride = GST_VIDEO_FRAME_COMP_PSTRIDE (frame, 0);
  row_wrap = stride - pixel_stride * width;

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      r = data[offsets[0]];
      g = data[offsets[1]];
      b = data[offsets[2]];

      y = APPLY_MATRIX (cog_rgb_to_ycbcr_matrix_8bit_sdtv, 0, r, g, b);
      u_tmp = APPLY_MATRIX (cog_rgb_to_ycbcr_matrix_8bit_sdtv, 1, r, g, b);
      v_tmp = APPLY_MATRIX (cog_rgb_to_ycbcr_matrix_8bit_sdtv, 2, r, g, b);

      y = CLAMP (y, 0, 255);
      u_tmp = CLAMP (u_tmp, 0, 255);
      v_tmp = CLAMP (v_tmp, 0, 255);

      y = tabley[y];
      u = tableu[u_tmp][v_tmp];
      v = tablev[u_tmp][v_tmp];

      r = APPLY_MATRIX (cog_ycbcr_to_rgb_matrix_8bit_sdtv, 0, y, u, v);
      g = APPLY_MATRIX (cog_ycbcr_to_rgb_matrix_8bit_sdtv, 1, y, u, v);
      b = APPLY_MATRIX (cog_ycbcr_to_rgb_matrix_8bit_sdtv, 2, y, u, v);

      data[offsets[0]] = CLAMP (r, 0, 255);
      data[offsets[1]] = CLAMP (g, 0, 255);
      data[offsets[2]] = CLAMP (b, 0, 255);
      data += pixel_stride;
    }
    data += row_wrap;
  }
}
