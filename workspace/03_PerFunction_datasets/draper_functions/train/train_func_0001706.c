getEaster(int year)
{
  int g, c, x, z, d, e, n, m;

  g=year%19+1;
  c=year/100+1;
  x=3*c/4-12;
  z=(8*c+5)/25-5;
  d=5*year/4-x-10;
  e=(11*g+20+z-x)%30;
  if ((e==25 && g>11) || e==24) e++;
  n=44-e;
  if (n<21) n+=30;
  n+=7-(d+n)%7;
  if (n>31) {n-=31; m=4;} else m=3;
  return date2julian(year,m,n);
}
