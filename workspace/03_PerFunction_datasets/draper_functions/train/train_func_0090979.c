vnl_gamma_series(double a, double x)
{
  if (x>0)
  {
    double a_i=a;
    double term_i=1.0/a;
    double sum = term_i;
    for (int i=1;i<=MAX_ITS;++i)
    {
      a_i+=1;
      term_i *= x/a_i;
      sum += term_i;
      if (std::fabs(term_i) < std::fabs(sum)*MaxRelError)
        return sum*std::exp(-x+a*std::log(x)-vnl_log_gamma(a));
    }
    std::cerr<<"vnl_gamma_series : Failed to converge in "<<MAX_ITS<<" steps\n"
            <<"a = "<<a<<"   x= "<< x <<"\nReturning best guess.\n";
    return sum*std::exp(-x+a*std::log(x)-vnl_log_gamma(a));
  }
  else if (x < 0.0)
    assert(!"vnl_gamma_series - x less than 0");

  return 0.0;
}
