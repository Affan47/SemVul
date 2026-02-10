series_2(double r, gsl_sf_result * result)
{
  static const int kmax = 100;
  double rk = r;
  double sum = 0.5 * r;
  int k;
  for(k=2; k<10; k++)
  {
    double ds;
    rk *= r;
    ds = rk/(k*k*(k+1.0));
    sum += ds;
  }
  for(; k<kmax; k++)
  {
    double ds;
    rk *= r;
    ds = rk/(k*k*(k+1.0));
    sum += ds;
    if(fabs(ds/sum) < 0.5*GSL_DBL_EPSILON) break;
  }

  result->val = sum;
  result->err = 2.0 * kmax * GSL_DBL_EPSILON * fabs(sum);

  return GSL_SUCCESS;
}
