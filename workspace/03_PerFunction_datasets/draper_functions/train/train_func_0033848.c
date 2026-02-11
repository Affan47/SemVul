main (int argc, char **argv)
{
  mp_ptr ap, bp, rp, refp;
  mp_size_t max_n, n;
  gmp_randstate_ptr rands;
  long test, reps = 1000;
  TMP_SDECL;
  TMP_SMARK;

  tests_start ();
  TESTS_REPS (reps, argv, argc);

  rands = RANDS;

  max_n = 32;

  ap = TMP_SALLOC_LIMBS (max_n);
  bp = TMP_SALLOC_LIMBS (max_n);
  rp = TMP_SALLOC_LIMBS (max_n);
  refp = TMP_SALLOC_LIMBS (max_n);

  for (test = 0; test < reps; test++)
    {
      for (n = 1; n <= max_n; n++)
	{
	  mpn_random2 (ap, n);
	  mpn_random2 (bp, n);

	  refmpn_and_n (refp, ap, bp, n);
	  mpn_and_n (rp, ap, bp, n);
	  check_one (refp, rp, ap, bp, n, "and");

	  refmpn_ior_n (refp, ap, bp, n);
	  mpn_ior_n (rp, ap, bp, n);
	  check_one (refp, rp, ap, bp, n, "ior");

	  refmpn_xor_n (refp, ap, bp, n);
	  mpn_xor_n (rp, ap, bp, n);
	  check_one (refp, rp, ap, bp, n, "xor");

	  refmpn_andn_n (refp, ap, bp, n);
	  mpn_andn_n (rp, ap, bp, n);
	  check_one (refp, rp, ap, bp, n, "andn");

	  refmpn_iorn_n (refp, ap, bp, n);
	  mpn_iorn_n (rp, ap, bp, n);
	  check_one (refp, rp, ap, bp, n, "iorn");

	  refmpn_nand_n (refp, ap, bp, n);
	  mpn_nand_n (rp, ap, bp, n);
	  check_one (refp, rp, ap, bp, n, "nand");

	  refmpn_nior_n (refp, ap, bp, n);
	  mpn_nior_n (rp, ap, bp, n);
	  check_one (refp, rp, ap, bp, n, "nior");

	  refmpn_xnor_n (refp, ap, bp, n);
	  mpn_xnor_n (rp, ap, bp, n);
	  check_one (refp, rp, ap, bp, n, "xnor");
	}
    }

  TMP_SFREE;
  tests_end ();
  return 0;
}
