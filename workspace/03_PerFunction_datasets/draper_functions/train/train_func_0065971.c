wei_func(double *p, int nparam, void *dptr)
{
  double lambda, tau;
  struct wei_data *data;
  double logL;
  int    i;


  lambda = exp(p[0]);
  tau    = exp(p[1]);
  data   = (struct wei_data *) dptr;

  logL = 0.;
  for (i = 0; i < data->n; i++)
    {
      if (tau < 1. && data->x[i] == data->mu) continue;
      logL += esl_wei_logpdf(data->x[i], data->mu, lambda, tau);
    }
  return -logL;
}
