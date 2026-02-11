min(double ra[],unsigned long n)
{
  double a;
  unsigned long i;
  a=ra[1];
  for(i=2;i<=n;i++){if (a>ra[i]) {a=ra[i];}}
  return(a);
}
