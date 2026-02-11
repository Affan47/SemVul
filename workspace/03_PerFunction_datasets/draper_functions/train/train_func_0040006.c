mptodouble (lrs_mp a, double *x)
{
  long i, la;
  double y = 1.0;

  (*x) = 0;
  la = length (a);
  for (i = 1; i < la; i++)
    {
      (*x) = (*x) + y * a[i];
      y = y * BASE;
    }
  if (negative (a))
    (*x)= -(*x);
}
