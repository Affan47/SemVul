prime_factor_multiplicities(map_integer_uint &primes_mul, const Integer &n)
{
    mpz_class sqrtN;
    mpz_class _n = n.as_mpz();
    unsigned count;
    if (_n == 0) return;
    if (_n < 0) _n *= -1;

    sqrtN = sqrt(_n);
    if (!sqrtN.fits_uint_p())
        throw std::runtime_error("N too large to factor");
    unsigned limit = sqrtN.get_ui();
    Sieve::iterator pi(limit);

    unsigned p;
    while ((p = pi.next_prime()) <= limit) {
        count = 0;
        while (_n % p == 0) {
            count++;
            _n = _n / p;
        }
        if (count > 0) {
            insert(primes_mul, integer(p), count);
            if (_n == 1) break;
        }
    }
    if (!(_n == 1))
        insert(primes_mul, integer(_n), 1);
}
