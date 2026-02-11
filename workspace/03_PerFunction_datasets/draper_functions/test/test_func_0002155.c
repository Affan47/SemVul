jacobi_hook (void *p, mp_srcptr gp, mp_size_t gn,
	     mp_srcptr qp, mp_size_t qn, int d)
{
  unsigned *bitsp = (unsigned *) p;

  if (gp)
    {
      ASSERT (gn > 0);
      if (gn != 1 || gp[0] != 1)
	{
	  *bitsp = BITS_FAIL;
	  return;
	}
    }

  if (qp)
    {
      ASSERT (qn > 0);
      ASSERT (d >= 0);
      *bitsp = mpn_jacobi_update (*bitsp, d, qp[0] & 3);
    }
}
