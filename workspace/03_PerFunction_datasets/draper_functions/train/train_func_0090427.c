circuit_build_times_calculate_timeout(circuit_build_times_t *cbt,
                                      double quantile)
{
  double ret;
  tor_assert(quantile >= 0);
  tor_assert(1.0-quantile > 0);
  tor_assert(cbt->Xm > 0);

  ret = cbt->Xm/pow(1.0-quantile,1.0/cbt->alpha);
  if (ret > INT32_MAX) {
    ret = INT32_MAX;
  }
  tor_assert(ret > 0);
  return ret;
}
