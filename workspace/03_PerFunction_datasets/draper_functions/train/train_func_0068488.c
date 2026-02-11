init_sieve_primes(unsigned int q)
{
  if (sieve_primes == NULL)
  {


    const unsigned char primes8[] = {
      3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
      71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
      149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211 };

    unsigned long buf[(46339-3)/(2*ULONG_BIT)];
    unsigned int i, j, q, r;

    memset(buf,-1,sizeof(buf));
    for (i = 0; i < sizeof(primes8); i++)
    {
      q = primes8[i];
      for (r = (q-3)/2+q; r < (46339-3)/2; r += q)
        buf[r/ULONG_BIT] &= ~(1UL << r%ULONG_BIT);
    }

    sieve_primes = xmalloc((4791+1)*sizeof(unsigned int));
    for (i = 0, j = 0; i < (46339-3)/2; i++)
      if (buf[i/ULONG_BIT] & (1UL << i%ULONG_BIT))
        sieve_primes[j++] = 3+2*i;
    assert(j == 4791);
    sieve_primes[4791] = -1U;
    num_sieve_primes = 4791;
    lim_sieve_primes = 46348;
  }

  extend_sieve_primes(q);

#ifndef NDEBUG
  printf("init_sieve_primes: Generated %u odd primes, max=%u, lim=%u\n",
         num_sieve_primes,sieve_primes[num_sieve_primes-1],lim_sieve_primes);
#endif
}
