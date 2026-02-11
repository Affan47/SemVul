eratosthenes_sieve(unsigned limit, std::vector<unsigned> &primes)
{
    std::vector<bool> is_prime(limit, true);
    const unsigned sqrt_limit = static_cast<unsigned>(std::sqrt(limit));
    for (unsigned n = 2; n <= sqrt_limit; ++n)
        if (is_prime[n]) {
            primes.push_back(n);
            for (unsigned k = n*n, ulim = limit; k < ulim; k += n)
                is_prime[k] = false;
        }
    for (unsigned n = sqrt_limit + 1; n < limit; ++n)
        if (is_prime[n])
            primes.push_back(n);
}
