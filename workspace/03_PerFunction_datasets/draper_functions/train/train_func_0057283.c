rotate_map (GstGeometricTransform * gt, gint x, gint y, gdouble * in_x,
    gdouble * in_y)
{
  GstRotate *rotate = GST_ROTATE_CAST (gt);
  gint w, h;
  gdouble cix, ciy, cox, coy;
  gdouble ai, ao, ar;
  gdouble r;
  gdouble xi, yi, xo, yo;


  w = gt->width;
  h = gt->height;


  ar = rotate->angle;


  cox = 0.5 * w;
  coy = 0.5 * h;
  cix = cox;
  ciy = coy;


  xo = x - cox;
  yo = y - coy;
  ao = atan2 (yo, xo);
  r = sqrt (xo * xo + yo * yo);


  ai = ao + ar;


  xi = r * cos (ai);
  yi = r * sin (ai);


  *in_x = xi + cix;
  *in_y = yi + ciy;

  GST_DEBUG_OBJECT (rotate, "Inversely mapped %d %d into %lf %lf",
      x, y, *in_x, *in_y);

  return TRUE;
}
