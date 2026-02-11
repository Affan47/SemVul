check_one (mp_srcptr ap, mp_size_t n, mp_limb_t b)
{
  mp_limb_t r_ref = refmpn_mod_1 (ap, n, b);
  mp_limb_t r;

  if (n >= 2)
    {
      mp_limb_t pre[4];
      mpn_mod_1_1p_cps (pre, b);
      r = mpn_mod_1_1p (ap, n, b << pre[1], pre);
      if (r != r_ref)
	{
	  printf ("mpn_mod_1_1p failed\n");
	  goto fail;
	}
    }
  if ((b & GMP_NUMB_HIGHBIT) == 0)
    {
      mp_limb_t pre[5];
      mpn_mod_1s_2p_cps (pre, b);
      r = mpn_mod_1s_2p (ap, n, b << pre[1], pre);
      if (r != r_ref)
	{
	  printf ("mpn_mod_1s_2p failed\n");
	  goto fail;
	}
    }
  if (b <= GMP_NUMB_MASK / 4)
    {
      mp_limb_t pre[7];
      mpn_mod_1s_4p_cps (pre, b);
      r = mpn_mod_1s_4p (ap, n, b << pre[1], pre);
      if (r != r_ref)
	{
	  printf ("mpn_mod_1s_4p failed\n");
	  goto fail;
	}
    }
  r = mpn_mod_1 (ap, n, b);
  if (r != r_ref)
    {
      printf ("mpn_mod_1 failed\n");
    fail:
      printf ("an = %d, a: ", (int) n); mpn_dump (ap, n);
      printf ("b           : "); mpn_dump (&b, 1);
      printf ("r (expected): "); mpn_dump (&r_ref, 1);
      printf ("r (bad)     : "); mpn_dump (&r, 1);
      abort();
    }
}
