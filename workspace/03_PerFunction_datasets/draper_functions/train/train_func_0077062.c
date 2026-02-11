SetResidualCoeffs(const int16_t* const coeffs,
                              VP8Residual* const res) {
  int n;
  res->last = -1;
  for (n = 15; n >= res->first; --n) {
    if (coeffs[n]) {
      res->last = n;
      break;
    }
  }
  res->coeffs = coeffs;
}
