gst_smpte_paint_box_clock (guint32 * dest, gint stride,
    gint x0, gint y0, gint c0,
    gint x1, gint y1, gint c1, gint x2, gint y2, gint c2)
{
  gfloat angle_m, col_m;
  gint xv, yv;

  if (x1 == x0) {
    xv = x2;
    yv = y1;
  } else if (y1 == y0) {
    xv = x1;
    yv = y2;
  } else {
    g_warning ("paint box clock: not supported");
    return;
  }

  angle_m = 2 * acos (((x1 - x0) * (xv - x0) + (y1 - y0) * (yv - y0)) /
      (sqrt ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)) *
          sqrt ((xv - x0) * (xv - x0) + (yv - y0) * (yv - y0)))) / M_PI;

  col_m = c2 * angle_m + c1 * (1.0 - angle_m);

  gst_smpte_paint_triangle_clock (dest, stride,
      x0, y0, c0, x1, y1, c1, xv, yv, col_m);
  gst_smpte_paint_triangle_clock (dest, stride,
      x0, y0, c0, xv, yv, col_m, x2, y2, c2);
}
