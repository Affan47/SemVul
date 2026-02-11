cpow_i(cmplx c, int n)
{
     if (n < 0)
	  return (1.0 / cpow_i(c, -n));
     else {
	  cmplx result = 1;
	  while (n > 1) {
	       if (n % 2 == 1)
		    result *= c;
	       c *= c;
	       n /= 2;
	  }
	  if (n > 0)
	       result *= c;
	  return result;
     }
}
