esl_hxp_logpdf(double x, ESL_HYPEREXP *h)
{
  int    k;
  double z;

  if (x < h->mu) return -eslINFINITY;

  for (k = 0; k < h->K; k++)
    if (h->q[k] == 0.0)
      h->wrk[k] = -eslINFINITY;
    else
      h->wrk[k] = log(h->q[k]) + esl_exp_logpdf(x, h->mu, h->lambda[k]);

  z = esl_vec_DLogSum(h->wrk, h->K);
  return z;
}
