difference_triangulated (GfsVertex * v, gpointer * data)
{
  GtsSurface * s = data[0];
  GfsVariable * var1 = data[1];
  GfsVariable * var2 = data[2];
  GfsVariable * e = data[3];
  GtsFace * f = gts_point_locate (GTS_POINT (v), s, NULL);

  if (f != NULL && gts_triangle_quality (GTS_TRIANGLE (f)) > 0.8) {
    GtsVertex * v1, * v2, * v3;
    gdouble x, x1, x2, y, y1, y2, a, b, det;
    gdouble fv3, fv1, fv2;

    gts_triangle_vertices (GTS_TRIANGLE (f), &v1, &v2, &v3);
    x = GTS_POINT (v)->x - GTS_POINT (v1)->x;
    y = GTS_POINT (v)->y - GTS_POINT (v1)->y;
    x1 = GTS_POINT (v2)->x - GTS_POINT (v1)->x;
    y1 = GTS_POINT (v2)->y - GTS_POINT (v1)->y;
    x2 = GTS_POINT (v3)->x - GTS_POINT (v1)->x;
    y2 = GTS_POINT (v3)->y - GTS_POINT (v1)->y;
    det = x1*y2 - x2*y1;
    g_assert (det != 0.);
    a = (x*y2 - y*x2)/det;
    b = (y*x1 - x*y1)/det;
    fv1 = GFS_VARIABLE (GFS_VERTEX (v1)->cell, var2->i);
    fv2 = GFS_VARIABLE (GFS_VERTEX (v2)->cell, var2->i);
    fv3 = GFS_VARIABLE (GFS_VERTEX (v3)->cell, var2->i);
    GTS_POINT (v)->z = GFS_VARIABLE (v->cell, e->i) =
      GFS_VARIABLE (v->cell, var1->i) -
      (fv1 + a*(fv2 - fv1) + b*(fv3 - fv1));
  }
}
