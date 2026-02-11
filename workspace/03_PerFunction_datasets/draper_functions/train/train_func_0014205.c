color_XYZ_to_xyY (Color * c)
{
  double d;
  d = c->v[0] + c->v[1] + c->v[2];
  if (d == 0) {
    c->v[0] = 0.3128;
    c->v[1] = 0.3290;
    c->v[2] = 0;
  } else {
    double x, y, Y;
    x = c->v[0] / d;
    y = c->v[1] / d;
    Y = c->v[1];
    c->v[0] = x;
    c->v[1] = y;
    c->v[2] = Y;
  }
}
