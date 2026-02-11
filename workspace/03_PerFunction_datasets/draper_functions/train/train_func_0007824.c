gst_vertigotv_set_parms (GstVertigoTV * filter)
{
  double vx, vy;
  double t;
  double x, y;
  double dizz;
  gint width, height;
  GstVideoInfo *info;

  dizz = sin (filter->phase) * 10 + sin (filter->phase * 1.9 + 5) * 5;

  info = &GST_VIDEO_FILTER (filter)->in_info;

  width = GST_VIDEO_INFO_WIDTH (info);
  height = GST_VIDEO_INFO_HEIGHT (info);

  x = width / 2;
  y = height / 2;

  t = (x * x + y * y) * filter->zoomrate;

  if (width > height) {
    if (dizz >= 0) {
      if (dizz > x)
        dizz = x;
      vx = (x * (x - dizz) + y * y) / t;
    } else {
      if (dizz < -x)
        dizz = -x;
      vx = (x * (x + dizz) + y * y) / t;
    }
    vy = (dizz * y) / t;
  } else {
    if (dizz >= 0) {
      if (dizz > y)
        dizz = y;
      vx = (x * x + y * (y - dizz)) / t;
    } else {
      if (dizz < -y)
        dizz = -y;
      vx = (x * x + y * (y + dizz)) / t;
    }
    vy = (dizz * x) / t;
  }
  filter->dx = vx * 65536;
  filter->dy = vy * 65536;
  filter->sx = (-vx * x + vy * y + x + cos (filter->phase * 5) * 2) * 65536;
  filter->sy = (-vx * y - vy * x + y + sin (filter->phase * 6) * 2) * 65536;

  filter->phase += filter->phase_increment;
  if (filter->phase > 5700000)
    filter->phase = 0;
}
