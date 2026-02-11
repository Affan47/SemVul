interpolator_scale (GfsInterpolator * a, gdouble b)
{
  guint i;
  for (i = 0; i < a->n; i++)
    a->w[i] *= b;
}
