esl_gam_invcdf(double p, double mu, double lambda, double tau)
{
  double x1, x2, xm;
  double f2, fm;
  double tol = 1e-6;

  x1 = 0.;
  x2 = tau / lambda;
  do {
    x2 = x2*2.;
    f2 = esl_gam_cdf(x2, mu, lambda, tau);
  } while (f2 < p);

  do {
    xm = (x1+x2)/ 2.;
    fm = esl_gam_cdf(xm, mu, lambda, tau);

    if      (fm > p) x2 = xm;
    else if (fm < p) x1 = xm;
    else return xm;
  } while ( (x2-x1)/(x1+x2) > tol);

  xm = (x1+x2)/2.;
  return xm;
}
