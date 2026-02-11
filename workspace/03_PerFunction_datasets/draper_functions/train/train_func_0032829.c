gsl_sf_hyperg_U_e(const double a, const double b, const double x, gsl_sf_result * result)
{
  gsl_sf_result_e10 re = {0};
  int stat_U = gsl_sf_hyperg_U_e10_e(a, b, x, &re);
  int stat_c = gsl_sf_result_smash_e(&re, result);
  return GSL_ERROR_SELECT_2(stat_c, stat_U);
}
