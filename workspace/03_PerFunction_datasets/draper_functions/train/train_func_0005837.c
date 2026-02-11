init_set_z (mpfr_ptr t, mpz_srcptr z)
{
  mpfr_prec_t p;
  int i;

  if (mpz_size (z) <= 1)
    p = GMP_NUMB_BITS;
  else
    MPFR_MPZ_SIZEINBASE2 (p, z);
  mpfr_init2 (t, p);
  i = mpfr_set_z (t, z, MPFR_RNDN);


  MPFR_ASSERTN (i == 0);  (void) i;
}
