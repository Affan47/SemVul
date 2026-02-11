mpfr_urandomb (mpfr_ptr rop, gmp_randstate_t rstate)
{
  mpfr_limb_ptr rp;
  mpfr_prec_t nbits;
  mp_size_t nlimbs;
  mp_size_t k;
  mpfr_exp_t exp;
  int cnt;

  rp = MPFR_MANT (rop);
  nbits = MPFR_PREC (rop);
  nlimbs = MPFR_LIMB_SIZE (rop);
  MPFR_SET_POS (rop);
  cnt = nlimbs * GMP_NUMB_BITS - nbits;


  mpfr_rand_raw (rp, rstate, nbits);
  if (MPFR_LIKELY (cnt != 0))
    mpn_lshift (rp, rp, nlimbs, cnt);


  exp = 0;
  k = 0;
  while (nlimbs != 0 && rp[nlimbs - 1] == 0)
    {
      k ++;
      nlimbs --;
      exp -= GMP_NUMB_BITS;
    }

  if (MPFR_LIKELY (nlimbs != 0))
    {
      count_leading_zeros (cnt, rp[nlimbs - 1]);

      if (mpfr_set_exp (rop, exp - cnt))
        {


          MPFR_SET_NAN (rop);
          __gmpfr_flags |= MPFR_FLAGS_NAN;
          return 1;
        }
      if (cnt != 0)
        mpn_lshift (rp + k, rp, nlimbs, cnt);
      if (k != 0)
        MPN_ZERO (rp, k);
    }
  else
    MPFR_SET_ZERO (rop);

  return 0;
}
