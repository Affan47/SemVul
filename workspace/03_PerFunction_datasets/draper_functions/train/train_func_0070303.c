theta_1d_0(unsigned long a, unsigned long b, unsigned long c,
				                                          long * out, ulong start, ulong len)
{

   for(ulong i = 0; i < len; i++)
      out[i] = 0;

   ulong i, j, x;

   if (start == 0)
   {
      long disc = b*b - 4*a*c;

	   if (disc < 0L)
	   {
		  x = 0;

		  i = a*x*x + b*x + c;

		  while (i < len)
        {
           out[i] += 1;

	        i += (a*x + b);
	        x += 1;
		     i += (a*x);
        }
	  } else
	  {
		  x = 0;

		  j = a*x*x + b*x + c;

		  while (j < (long) len)
        {
           if (j >= 0L) out[j] += 1;

	        j += (a*x + b);
	        x += 1;
		     j += (a*x);
        }
	  }
   } else
   {
      x = z_intsqrt(start/a-1)+1;

      while (a*x*x - b*x + c < start) x++;

      i = a*x*x - b*x + c - start;

      while (i < len)
      {
         out[i] += 1;

	     i += (a*x - b);
	     x += 1;
		 i += (a*x);
      }
   }
}
