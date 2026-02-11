z_mulmod_precomp(unsigned long a, unsigned long b,
                                         unsigned long n, double ninv)
{
   unsigned long quot = (unsigned long) ((double) a * (double) b * ninv);
   long rem = a*b - quot*n;
   if (rem < 0)
   {
      rem += n;
      if (rem < 0) return rem + n;
   } else if (rem >= n) return rem - n;
   return rem;
}
