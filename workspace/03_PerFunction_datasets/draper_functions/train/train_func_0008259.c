check_one (mp_ptr qp, mp_srcptr rp, mp_limb_t rh,
	   mp_srcptr np, mp_size_t nn, mp_srcptr dp, mp_size_t dn, char *fname)
{
  mp_size_t qn;
  int cmp;
  mp_ptr tp;
  mp_limb_t cy = 4711;
  TMP_DECL;

  qn = nn - dn;

  if (qn == 0)
    return;

  TMP_MARK;

  tp = TMP_ALLOC_LIMBS (nn + 1);

  if (dn >= qn)
    mpn_mul (tp, dp, dn, qp, qn);
  else
    mpn_mul (tp, qp, qn, dp, dn);

  if (rp != NULL)
    {
      cy = mpn_add_n (tp + qn, tp + qn, rp, dn);
      cmp = cy != rh || mpn_cmp (tp, np, nn) != 0;
    }
  else
    cmp = mpn_cmp (tp, np, nn - dn) != 0;

  if (cmp != 0)
    {
      printf ("\r*******************************************************************************\n");
      printf ("%s inconsistent in test %lu\n", fname, test);
      printf ("N=   "); dumpy (np, nn);
      printf ("D=   "); dumpy (dp, dn);
      printf ("Q=   "); dumpy (qp, qn);
      if (rp != NULL)
	{
	  printf ("R=   "); dumpy (rp, dn);
	  printf ("Rb=  %d, Cy=%d\n", (int) cy, (int) rh);
	}
      printf ("T=   "); dumpy (tp, nn);
      printf ("nn = %ld, dn = %ld, qn = %ld", nn, dn, qn);
      printf ("\n*******************************************************************************\n");
      abort ();
    }

  TMP_FREE;
}
