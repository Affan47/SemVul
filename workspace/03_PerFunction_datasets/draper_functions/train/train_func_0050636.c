update_offsets(unsigned long poly_add, unsigned long * poly_corr,
             QS_t * qs_inf, poly_t * poly_inf)
{
   unsigned long num_primes = qs_inf->num_primes;
   unsigned long * soln1 = poly_inf->soln1;
   unsigned long * soln2 = poly_inf->soln2;
   prime_t * factor_base = qs_inf->factor_base;
   unsigned long p, correction;

   for (unsigned long prime = 2; prime < num_primes; prime++)
   {
      p = factor_base[prime].p;
      correction = (poly_add ? p - poly_corr[prime] : poly_corr[prime]);
      soln1[prime] += correction;
      if (soln1[prime] >= p) soln1[prime] -= p;
      if (soln2[prime] == -1L) continue;
      soln2[prime] += correction;
      if (soln2[prime] >= p) soln2[prime] -= p;
   }
}
