gsl_diff_backward (const gsl_function * f,
                   double x, double *result, double *abserr)
{


  int i, k;
  double h = GSL_SQRT_DBL_EPSILON;
  double a[3], d[3], a2;


  for (i = 0; i < 3; i++)
    {
      a[i] = x + (i - 2.0) * h;
      d[i] = GSL_FN_EVAL (f, a[i]);
    }

  for (k = 1; k < 4; k++)
    {
      for (i = 0; i < 3 - k; i++)
        {
          d[i] = (d[i + 1] - d[i]) / (a[i + k] - a[i]);
        }
    }


  a2 = fabs (d[0] + d[1] + d[2]);

  if (a2 < 100.0 * GSL_SQRT_DBL_EPSILON)
    {
      a2 = 100.0 * GSL_SQRT_DBL_EPSILON;
    }

  h = sqrt (GSL_SQRT_DBL_EPSILON / (2.0 * a2));

  if (h > 100.0 * GSL_SQRT_DBL_EPSILON)
    {
      h = 100.0 * GSL_SQRT_DBL_EPSILON;
    }

  *result = (GSL_FN_EVAL (f, x) - GSL_FN_EVAL (f, x - h)) / h;
  *abserr = fabs (10.0 * a2 * h);

  return GSL_SUCCESS;
}
