esl_hxp_FitGuessBinned(ESL_HISTOGRAM *g, ESL_HYPEREXP *h)
{
  double sum;
  int    n;
  int    i,k;
  int    nb;
  double ai;

  if      (g->is_tailfit) h->mu = g->phi;
  else if (g->is_rounded) h->mu = esl_histogram_Bin2LBound(g, g->imin);
  else                    h->mu = g->xmin;

  nb    = g->imax - g->cmin + 1;
  k     = h->K-1;
  sum   = 0;
  n     = 0;
  for (i = g->imax; i >= g->cmin; i--)
    {
      ai = esl_histogram_Bin2LBound(g,i);
      if (ai < g->xmin) ai = g->xmin;
      n      += g->obs[i];
      sum    += g->obs[i] * ai;

      if (i == g->cmin + (k*nb)/h->K)
	h->lambda[k--] = 1 / ((sum/(double) n) - ai);
    }

  if (! h->fixmix) {
    for (k = 0; k < h->K; k++)
      h->q[k] = 1 / (double) h->K;
  }

  return eslOK;
}
