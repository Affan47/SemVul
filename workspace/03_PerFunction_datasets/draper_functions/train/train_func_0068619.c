generic_limiter (gdouble r, gdouble beta)
{
  gdouble v1 = MIN (r, beta), v2 = MIN (beta*r, 1.);
  v1 = MAX (0., v1);
  return MAX (v1, v2);
}
