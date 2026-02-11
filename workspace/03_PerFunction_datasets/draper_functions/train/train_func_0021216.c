gsl_cdf_weibull_Qinv (const double Q, const double a, const double b)
{
  double x;

  if (Q == 0.0)
    {
      return GSL_POSINF;
    }
  else if (Q == 1.0)
    {
      return 0.0;
    }

  x = a * pow(-log(Q), 1/b);

  return x;
}
