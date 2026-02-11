esl_mixgev_invcdf(double p, ESL_MIXGEV *mg)
{
  double x1, x2, xm;
  double f1, f2, fm;
  double tol = 1e-6;

  x2 = esl_vec_DMin(mg->mu, mg->K);
  x1 = x2 - 1.;
  do {
    x1 = x1 + 2.*(x2-x1);
    f1 = esl_mixgev_cdf(x1, mg);
  } while (f1 > p);
  do {
    x2 = x2 + 2.*(x2-x1);
    f2 = esl_mixgev_cdf(x2, mg);
  } while (f2 < p);

  do {
    xm = (x1+x2) / 2.;
    fm = esl_mixgev_cdf(xm, mg);

    if      (fm > p) x2 = xm;
    else if (fm < p) x1 = xm;
    else return xm;
  } while ( (x2-x1)/(x1+x2+1e-9) > tol);

  xm = (x1+x2) / 2.;
  return xm;
}
