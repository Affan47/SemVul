z_nextprime(unsigned long n, int proved)
{
   if (n < 7)
   {
      if (n<2) return 2;
      n++;
      n|=1;
      return n;
   }

   unsigned long index = n%30;
   n+=nextmod30[index];
   index = nextindex[index];

   if (n <= z_primes[NEXTPRIME_PRIMES-1])
   {
      if (n == 7) return 7;
      if (n == 11) return 11;
      if (n == 13) return 13;

      while (((n%7)==0)||((n%11)==0)||((n%13)==0))
      {
         n += nextmod30[index];
         index = nextindex[index];
      }
      return n;
   }

   unsigned int * moduli = (unsigned int *) flint_stack_alloc_bytes(NEXTPRIME_PRIMES * sizeof(unsigned int));

   for (unsigned int i = 3; i < NEXTPRIME_PRIMES; i++)
      moduli[i] = (n % z_primes[i]);

   while (1)
   {
      unsigned int composite = 0;

      unsigned int diff, acc, pr;;

      diff = nextmod30[index];


      for (unsigned int i = 3; i < NEXTPRIME_PRIMES; i++)
	   {
	      composite |= (moduli[i] == 0);
	      acc = moduli[i] + diff;
	      pr = z_primes[i];
	      moduli[i] = acc >= pr ? acc - pr : acc;
	   }
      if (composite)
      {
	      n += diff;
         index = nextindex[index];
         continue;
      }

      if ((!proved && z_isprobab_prime(n)) || (proved && z_isprime(n))) break;
      else
      {
         n += diff;
         index = nextindex[index];
      }
   }

   flint_stack_release();

   return n;
}
