dilogc_series_1(
  const double r,
  const double x,
  const double y,
  gsl_sf_result * real_result,
  gsl_sf_result * imag_result
  )
{
  const double cos_theta = x/r;
  const double sin_theta = y/r;
  const double alpha = 1.0 - cos_theta;
  const double beta  = sin_theta;
  double ck = cos_theta;
  double sk = sin_theta;
  double rk = r;
  double real_sum = r*ck;
  double imag_sum = r*sk;
  const int kmax = 50 + (int)(22.0/(-log(r)));
  int k;
  for(k=2; k<kmax; k++) {
    double dr, di;
    double ck_tmp = ck;
    ck = ck - (alpha*ck + beta*sk);
    sk = sk - (alpha*sk - beta*ck_tmp);
    rk *= r;
    dr = rk/((double)k*k) * ck;
    di = rk/((double)k*k) * sk;
    real_sum += dr;
    imag_sum += di;
    if(fabs((dr*dr + di*di)/(real_sum*real_sum + imag_sum*imag_sum)) < GSL_DBL_EPSILON*GSL_DBL_EPSILON) break;
  }

  real_result->val = real_sum;
  real_result->err = 2.0 * kmax * GSL_DBL_EPSILON * fabs(real_sum);
  imag_result->val = imag_sum;
  imag_result->err = 2.0 * kmax * GSL_DBL_EPSILON * fabs(imag_sum);

  return GSL_SUCCESS;
}
