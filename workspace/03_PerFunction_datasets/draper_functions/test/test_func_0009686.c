gst_text_overlay_blit_sub2x2 (GstCairoTextOverlay * overlay, guchar * dest,
    guchar * text_image, gint val, guint dest_stride, gint y0)
{
  gint i, j;
  gint x, a, y;
  gint y1;

  y0 = MIN (y0, overlay->height);
  y1 = MIN (y0 + overlay->font_height, overlay->height);

  y = val;

  for (i = y0; i < y1; i += 2) {
    for (j = 0; j < overlay->width; j += 2) {
      x = dest[(i / 2) * dest_stride + j / 2];
      a = (text_image[4 * ((i - y0) * overlay->width + j) + 1] +
          text_image[4 * ((i - y0) * overlay->width + j + 1) + 1] +
          text_image[4 * ((i - y0 + 1) * overlay->width + j) + 1] +
          text_image[4 * ((i - y0 + 1) * overlay->width + j + 1) + 1] + 2) / 4;
      dest[(i / 2) * dest_stride + j / 2] = (y * a + x * (255 - a)) / 255;
    }
  }
}
