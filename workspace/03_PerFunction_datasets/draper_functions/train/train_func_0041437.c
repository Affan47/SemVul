gsl_ran_rayleigh_pdf (const double x, const double sigma)
{
  if (x < 0)
    {
      return 0 ;
    }
  else
    {
      double u = x / sigma ;
      double p = (u / sigma) * exp(-u * u / 2.0) ;

      return p;
    }
}
