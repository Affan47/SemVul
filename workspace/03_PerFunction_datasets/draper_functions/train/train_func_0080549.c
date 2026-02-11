gst_text_overlay_shade_y (GstCairoTextOverlay * overlay, guchar * dest,
    guint dest_stride, gint y0, gint y1)
{
  gint i, j, x0, x1;

  x0 = CLAMP (overlay->text_x0 - BOX_XPAD, 0, overlay->width);
  x1 = CLAMP (overlay->text_x1 + BOX_XPAD, 0, overlay->width);

  y0 = CLAMP (y0 - BOX_YPAD, 0, overlay->height);
  y1 = CLAMP (y1 + BOX_YPAD, 0, overlay->height);

  for (i = y0; i < y1; ++i) {
    for (j = x0; j < x1; ++j) {
      gint y = dest[(i * dest_stride) + j] + BOX_SHADING_VAL;

      dest[(i * dest_stride) + j] = CLAMP (y, 0, 255);
    }
  }
}
