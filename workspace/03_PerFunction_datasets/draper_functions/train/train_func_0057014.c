main (int argc, char **argv)
{
  mp_limb_t a;
  mp_ptr pp, scratch;
  mp_limb_t max_b;
  int count = COUNT;
  int test;
  gmp_randstate_ptr rands;
  TMP_DECL;

  if (argc > 1)
    {
      char *end;
      count = strtol (argv[1], &end, 0);
      if (*end || count <= 0)
	{
	  fprintf (stderr, "Invalid test count: %s.\n", argv[1]);
	  return 1;
	}
    }

  tests_start ();
  TMP_MARK;
  rands = RANDS;

  pp = TMP_ALLOC_LIMBS (MAX_N);
  scratch = TMP_ALLOC_LIMBS (MAX_N);
  max_b = numberof (mp_bases);

  ASSERT_ALWAYS (max_b > 62);
  ASSERT_ALWAYS (max_b < GMP_NUMB_MAX);

  for (a = 2; a < max_b; ++a)
    for (test = 0; test < count; ++test)
      {
	mp_size_t pn;
	mp_limb_t exp;
	mp_bitcnt_t res;

	exp = gmp_urandomm_ui (rands, MAX_N);

	pn = mpn_pow_1 (pp, &a, 1, exp, scratch);

	res = mpn_sizeinbase (pp, pn, a) - 1;

	if ((res < exp) || (res > exp + 1))
	  {
	    printf ("ERROR in test %d, base = %d, exp = %d, res = %d\n",
		    test, (int) a, (int) exp, (int) res);
	    abort();
	  }

	mpn_sub_1 (pp, pp, pn, CNST_LIMB(1));
	pn -= pp[pn-1] == 0;

	res = mpn_sizeinbase (pp, pn, a);

	if ((res < exp) || (res - 1 > exp))
	  {
	    printf ("ERROR in -1 test %d, base = %d, exp = %d, res = %d\n",
		    test, (int) a, (int) exp, (int) res);
	    abort();
	  }
      }

  TMP_FREE;
  tests_end ();
  return 0;
}
