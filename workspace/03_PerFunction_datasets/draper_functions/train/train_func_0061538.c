gsl_deriv_forward (const gsl_function * f, double x, double h,
                   double *result, double *abserr)
{
  double r_0, round, trunc, error;
  forward_deriv (f, x, h, &r_0, &round, &trunc);
  error = round + trunc;

  if (round < trunc && (round > 0 && trunc > 0))
    {
      double r_opt, round_opt, trunc_opt, error_opt;


      double h_opt = h * pow (round / (trunc), 1.0 / 2.0);
      forward_deriv (f, x, h_opt, &r_opt, &round_opt, &trunc_opt);
      error_opt = round_opt + trunc_opt;


      if (error_opt < error && fabs (r_opt - r_0) < 4.0 * error)
        {
          r_0 = r_opt;
          error = error_opt;
        }
    }

  *result = r_0;
  *abserr = error;

  return GSL_SUCCESS;
}
