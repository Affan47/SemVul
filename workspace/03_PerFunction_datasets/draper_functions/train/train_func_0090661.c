gsl_cdf_binomial_P (const unsigned int k, const double p, const unsigned int n) {
  double P;
  double a;
  double b;

  if (p > 1.0 || p < 0.0) {
    fprintf(stderr,"p < 0 or p > 1\n");
    abort();
  }

  if (k >= n) {
    P = 1.0;
  } else {
    a = (double) k + 1.0;
    b = (double) n - k;
    P = gsl_cdf_beta_Q (p, a, b);
  }

  return P;
}
