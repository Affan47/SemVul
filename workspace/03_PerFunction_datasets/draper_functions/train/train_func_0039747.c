gsl_complex_pow_real (gsl_complex a, double b)
{
  gsl_complex z;

  if (GSL_REAL (a) == 0 && GSL_IMAG (a) == 0)
    {
      if (b == 0)
        {
          GSL_SET_COMPLEX (&z, 1, 0);
        }
      else
        {
          GSL_SET_COMPLEX (&z, 0, 0);
        }
    }
  else
    {
      double logr = gsl_complex_logabs (a);
      double theta = gsl_complex_arg (a);
      double rho = exp (logr * b);
      double beta = theta * b;
      GSL_SET_COMPLEX (&z, rho * cos (beta), rho * sin (beta));
    }

  return z;
}
