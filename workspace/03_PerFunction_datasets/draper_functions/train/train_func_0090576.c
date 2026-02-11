cyc_splint(double const *xa,
                         double const *ya,
                         double const *y2a,
                         int n,
                         double period,
                         double x)
{
  int klo = -1;
  int khi = n;
  int k;
  double xlo = xa[n-1] - period;
  double xhi = xa[0] + period;
  while (khi-klo > 1) {
    k = (khi+klo) >> 1;
    if (xa[k] > x) {
      khi = k;
      xhi = xa[k];
    }
    else {
      klo = k;
      xlo = xa[k];
    }
  }

  if (khi == n) khi = 0;
  if (klo ==-1) klo = n-1;

  double h = xhi-xlo;
  double a = (xhi-x) / h;
  double b = (x-xlo) / h;
  double y = a*ya[klo] + b*ya[khi] +
    ((a*a*a-a)*y2a[klo] + (b*b*b-b)*y2a[khi]) * (h*h)/6.0;

  return y;

}
