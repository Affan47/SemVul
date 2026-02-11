check_rand (void)
{
  gmp_randstate_ptr rands = RANDS;
  int            rep, i;
  unsigned long  mant_bits;
  long           exp, exp_min, exp_max;
  double         got, want, d;
  mp_size_t      nalloc, nsize, sign;
  mp_limb_t      nhigh_mask;
  mp_ptr         np;

  mant_bits = tests_dbl_mant_bits ();
  if (mant_bits == 0)
    return;


  exp_min = -100 - mant_bits;
  exp_max =  100 - mant_bits;


  nalloc = BITS_TO_LIMBS (mant_bits);
  np = refmpn_malloc_limbs (nalloc);
  nhigh_mask = MP_LIMB_T_MAX
    >> (GMP_NAIL_BITS + nalloc * GMP_NUMB_BITS - mant_bits);

  for (rep = 0; rep < 200; rep++)
    {

      exp = exp_min + (long) gmp_urandomm_ui (rands, exp_max - exp_min + 1);


      if (rep & 1)
        mpn_random (np, nalloc);
      else
        mpn_random2 (np, nalloc);
      nsize = nalloc;
      np[nsize-1] &= nhigh_mask;
      MPN_NORMALIZE (np, nsize);
      if (nsize == 0)
        continue;

      sign = (mp_size_t) gmp_urandomb_ui (rands, 1L) - 1;


      want = 0.0;
      for (i = 0, d = 1.0; i < mant_bits; i++, d *= 2.0)
        if (np[i/GMP_NUMB_BITS] & (CNST_LIMB(1) << (i%GMP_NUMB_BITS)))
          want += d;
      if (sign < 0)
        want = -want;


      for (i = 0; i < exp; i++)
        want *= 2.0;
      for (i = 0; i > exp; i--)
        want *= 0.5;

      got = mpn_get_d (np, nsize, sign, exp);

      if (got != want)
        {
          printf    ("mpn_get_d wrong on random data\n");
          printf    ("   sign     %ld\n", (long) sign);
          mpn_trace ("   n        ", np, nsize);
          printf    ("   nsize    %ld\n", (long) nsize);
          printf    ("   exp      %ld\n", exp);
          d_trace   ("   want     ", want);
          d_trace   ("   got      ", got);
          abort();
        }
    }

  free (np);
}
