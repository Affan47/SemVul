mpp_fermat_list(mp_int *a, const mp_digit *primes, mp_size nPrimes)
{
  mp_err rv = MP_YES;

  while (nPrimes-- > 0 && rv == MP_YES) {
    rv = mpp_fermat(a, *primes++);
  }
  return rv;
}
