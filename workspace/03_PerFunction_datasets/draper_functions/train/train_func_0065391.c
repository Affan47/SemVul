esl_exp_FitCompleteScale(double *x, int n, double mu, double *ret_lambda)
{
  double mean;
  int    i;

  mean = 0.;
  for (i = 0; i < n; i++) mean += x[i] - mu;
  mean /= (double) n;

  *ret_lambda = 1./mean;
  return eslOK;
}
