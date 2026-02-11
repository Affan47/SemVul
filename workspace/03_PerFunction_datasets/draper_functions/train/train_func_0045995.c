param2Point(double u_p, double v_p)
{
  Point3 pp;

  double u = data.start_u + u_p * (data.end_u - data.start_u);

  param2Point_own(u, pp);

  GcPoint* p = new GcPoint(pp);

  return p;
}
