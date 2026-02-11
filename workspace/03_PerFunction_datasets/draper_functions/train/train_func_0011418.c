esl_sxp_logsurv(double x, double mu, double lambda, double tau)
{
  double y = lambda * (x-mu);
  double val;

  if (x <= mu) return 0.0;

  esl_stats_IncompleteGamma(1./tau, exp(tau * log(y)), NULL, &val);
  return log(val);
}
