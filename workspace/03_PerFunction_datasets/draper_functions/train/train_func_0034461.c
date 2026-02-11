Fn1( double x, int n )
{
  double const gam = 0.577215664901532860606512;
  double eps = 1.e-15;
  double se = 0.0;
  double se1 = -1.0;
  double so = x;
  double to = x;
  double so1 = 2.0*x;
  double s = x/2.0;
  for( int k=1;; ++k )
  {
    if( so-se<=eps*s || se<=se1 || so>=so1 )break;
    se1 = se;
    so1 = so;
    double te = (k*2-1)*x*to/(k*2*k*2);
    se += to-te;
    to = k*2*x*te/((k*2+1)*(k*2+1));
    so += to-te;
    s = (se+so)/2.0;
  }
  return (s-gam-log(x))*exp(x);
}
