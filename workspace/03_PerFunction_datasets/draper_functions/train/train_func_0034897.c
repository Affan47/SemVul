z_compute_extended_primes()
{
    unsigned int sieve[ETF_SIEVE_SIZE];
    unsigned int p,q,oldq = 0,n_found=0;
    unsigned int i, j;

    for (ulong j = 0; j < ETF_SIEVE_SIZE; j++)
       sieve[j] = 1;

    for (i = 1; z_primes[i]*z_primes[i] < 1000; i++)
    {
        p = z_primes[i];
        q = 1000-1000%p;
        q = q+(1+q%2)*p;
        q = q/2 - 500;
        while (q < ETF_SIEVE_SIZE)
        {
            sieve[q] = 0;
            q+=p;
        }
    }

    for (; i < TF_CUTOFF; i++)
    {
        p = z_primes[i];
        q = (p*p)/2 - 500;
        for (unsigned int j = oldq; j < q; j++)
        {
            if (sieve[j])
            {
                z_extended_primes[n_found] = 2*(j+500)+1;
                n_found++;
            }
        }
        oldq = q;
        while (q < ETF_SIEVE_SIZE)
        {
            sieve[q] = 0;
            q+=p;
        }
    }
    for (unsigned int j = oldq; j < ETF_NUM_PRIMES; j++)
    {
        if (sieve[j])
        {
            z_extended_primes[n_found] = 2*(j+500)+1;
            n_found++;
        }
    }
}
