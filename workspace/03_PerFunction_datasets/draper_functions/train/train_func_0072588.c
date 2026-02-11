fftw_factor(int n)
{
     int r;


     if ((n & 1) == 0)
	  return 2;


     for (r = 3; r * r <= n; r += 2)
	  if (n % r == 0)
	       return r;


     return n;
}
