mpz_eq_mpn (mp_ptr ap, mp_size_t an, const mpz_t b)
{
  mp_size_t bn = mpz_size (b);

  return (bn >= 0 && bn <= an
	  && mpn_cmp (ap, mpz_limbs_read (b), bn) == 0
	  && mpn_zero_p (ap + bn, an - bn));
}
