gst_alpha_set_rgb_ayuv (const guint8 * src, guint8 * dest, gint width,
    gint height, GstAlpha * alpha)
{
  gint s_alpha = CLAMP ((gint) (alpha->alpha * 255), 0, 255);
  gint i, j;
  gint matrix[12];
  gint y, u, v;
  gint o[3];
  gint bpp;

  bpp = gst_video_format_get_pixel_stride (alpha->in_format, 0);

  o[0] =
      gst_video_format_get_component_offset (alpha->in_format, 0, width,
      height);
  o[1] =
      gst_video_format_get_component_offset (alpha->in_format, 1, width,
      height);
  o[2] =
      gst_video_format_get_component_offset (alpha->in_format, 2, width,
      height);

  memcpy (matrix,
      alpha->out_sdtv ? cog_rgb_to_ycbcr_matrix_8bit_sdtv :
      cog_rgb_to_ycbcr_matrix_8bit_hdtv, 12 * sizeof (gint));

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      dest[0] = s_alpha;

      y = APPLY_MATRIX (matrix, 0, src[o[0]], src[o[1]], src[o[2]]);
      u = APPLY_MATRIX (matrix, 1, src[o[0]], src[o[1]], src[o[2]]);
      v = APPLY_MATRIX (matrix, 2, src[o[0]], src[o[1]], src[o[2]]);

      dest[1] = y;
      dest[2] = u;
      dest[3] = v;

      dest += 4;
      src += bpp;
    }
  }
}
