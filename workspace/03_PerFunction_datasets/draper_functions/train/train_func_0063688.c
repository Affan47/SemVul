interpolated_value (GtsSurface * s, FttVector * p)
{
  GtsPoint q;
  GtsFace * t;

  q.x = p->x; q.y = p->y;
  t = gts_point_locate (&q, s, NULL);
  if (t == NULL) {
    g_warning ("cannot locate point (%g,%g)", p->x, p->y);
    return 0.;
  }
  gts_triangle_interpolate_height (GTS_TRIANGLE (t), &q);
  return q.z;
}
