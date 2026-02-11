bounds_add (bounds *bnds, double_int delta, tree type)
{
  mpz_t mdelta, max;

  mpz_init (mdelta);
  mpz_set_double_int (mdelta, delta, false);

  mpz_init (max);
  mpz_set_double_int (max, double_int::mask (TYPE_PRECISION (type)), true);

  mpz_add (bnds->up, bnds->up, mdelta);
  mpz_add (bnds->below, bnds->below, mdelta);

  if (mpz_cmp (bnds->up, max) > 0)
    mpz_set (bnds->up, max);

  mpz_neg (max, max);
  if (mpz_cmp (bnds->below, max) < 0)
    mpz_set (bnds->below, max);

  mpz_clear (mdelta);
  mpz_clear (max);
}
