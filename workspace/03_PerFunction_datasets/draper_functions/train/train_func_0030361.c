esl_exp_logcdf(double x, double mu, double lambda)
{
  double y  = lambda * (x-mu);
  double ey = exp(-y);

  if (x < mu) return -eslINFINITY;


  if      (y == 0)           return -eslINFINITY;
  else if (y  < eslSMALLX1)  return log(y);
  else if (ey < eslSMALLX1)  return -ey;
  else                       return log(1-ey);
}
