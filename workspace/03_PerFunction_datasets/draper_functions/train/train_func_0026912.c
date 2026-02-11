do_sieving(QS_t * qs_inf, poly_t * poly_inf, unsigned char * sieve,
                  unsigned long first_prime, unsigned long second_prime,
                  unsigned long M, int first, int last)
{
   unsigned long num_primes = qs_inf->num_primes;
   uint32_t * soln1 = poly_inf->soln1;
   uint32_t * soln2 = poly_inf->soln2;
   uint32_t * posn1 = poly_inf->posn1;
   uint32_t * posn2 = poly_inf->posn2;
   prime_t * factor_base = qs_inf->factor_base;
   unsigned long small_primes = qs_inf->small_primes;
   unsigned long p, correction;
   register unsigned char * position;
   unsigned char * end = sieve + M;
   unsigned char * sizes = qs_inf->sizes;
   register unsigned char * pos1;
   unsigned char * pos2;
   register unsigned char * bound;
   unsigned long size;
   long diff;

   for (unsigned long prime = first_prime; prime < second_prime; prime++)
   {
      if (soln2[prime] == -1) continue;

      p = factor_base[prime].p;
      size = sizes[prime];
      if (first)
      {
         pos1 = sieve + soln1[prime];
         pos2 = sieve + soln2[prime];
      } else
      {
         pos1 = sieve + posn1[prime];
         pos2 = sieve + posn2[prime];
      }

      bound = end - p;

      while (bound - pos1 > 0)
      {
         (*pos1)+=size, pos1+=p, (*pos2)+=size, pos2+=p;
      }
      if ((end - pos1 > 0) && (end - pos2 > 0))
      {
         (*pos1)+=size, pos1+=p, (*pos2)+=size, pos2+=p;
      }
      if (end - pos2 > 0)
      {
         (*pos2)+=size, pos2+=p;
      }
      if (end - pos1 > 0)
      {
         (*pos1)+=size, pos1+=p;
      }

      if (!last)
      {
         posn1[prime] = pos1 - sieve;
         posn2[prime] = pos2 - sieve;
      }
   }

}
