gsl_complex_pow (gsl_complex a, gsl_complex b)
{
  gsl_complex z;

  if (GSL_REAL (a) == 0 && GSL_IMAG (a) == 0.0)
    {
      if (GSL_REAL (b) == 0 && GSL_IMAG (b) == 0.0)
        {
          GSL_SET_COMPLEX (&z, 1.0, 0.0);
        }
      else
        {
          GSL_SET_COMPLEX (&z, 0.0, 0.0);
        }
    }
  else if (GSL_REAL (b) == 1.0 && GSL_IMAG (b) == 0.0)
    {
      return a;
    }
  else if (GSL_REAL (b) == -1.0 && GSL_IMAG (b) == 0.0)
    {
      return gsl_complex_inverse (a);
    }
  else
    {
      double logr = gsl_complex_logabs (a);
      double theta = gsl_complex_arg (a);

      double br = GSL_REAL (b), bi = GSL_IMAG (b);

      double rho = exp (logr * br - bi * theta);
      double beta = theta * br + bi * logr;

      GSL_SET_COMPLEX (&z, rho * cos (beta), rho * sin (beta));
    }

  return z;
}
