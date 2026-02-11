diffuse_map (GstGeometricTransform * gt, gint x, gint y, gdouble * in_x,
    gdouble * in_y)
{
  GstDiffuse *diffuse = GST_DIFFUSE_CAST (gt);
  gint angle;
  gdouble distance;

  angle = g_random_int_range (0, 256);
  distance = g_random_double ();

  *in_x = x + distance * diffuse->sin_table[angle];
  *in_y = y + distance * diffuse->cos_table[angle];

  GST_DEBUG_OBJECT (diffuse, "Inversely mapped %d %d into %lf %lf",
      x, y, *in_x, *in_y);

  return TRUE;
}
