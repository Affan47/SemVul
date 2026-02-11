motiondetect (GstRippleTV * filter, guint32 * src)
{
  guint8 *diff = filter->diff;
  gint width = filter->width;
  gint *p, *q;
  gint x, y, h;

  if (!filter->bg_is_set)
    setBackground (filter, src);

  image_bgsubtract_update_y (src, filter->background, filter->diff,
      filter->width * filter->height);
  p = filter->map1 + filter->map_w + 1;
  q = filter->map2 + filter->map_w + 1;
  diff += filter->width + 2;

  for (y = filter->map_h - 2; y > 0; y--) {
    for (x = filter->map_w - 2; x > 0; x--) {
      h = (gint) * diff + (gint) * (diff + 1) + (gint) * (diff + width) +
          (gint) * (diff + width + 1);
      if (h > 0) {
        *p = h << (point + impact - 8);
        *q = *p;
      }
      p++;
      q++;
      diff += 2;
    }
    diff += width + 2;
    p += 2;
    q += 2;
  }
}
