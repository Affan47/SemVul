compute_v (mp_ptr vp,
	   mp_srcptr ap, mp_srcptr bp, mp_size_t n,
	   mp_srcptr gp, mp_size_t gn,
	   mp_srcptr up, mp_size_t usize,
	   mp_ptr tp)
{
  mp_size_t size;
  mp_size_t an;
  mp_size_t bn;
  mp_size_t vn;

  ASSERT (n > 0);
  ASSERT (gn > 0);
  ASSERT (usize != 0);

  size = ABS (usize);
  ASSERT (size <= n);
  ASSERT (up[size-1] > 0);

  an = n;
  MPN_NORMALIZE (ap, an);
  ASSERT (gn <= an);

  if (an >= size)
    mpn_mul (tp, ap, an, up, size);
  else
    mpn_mul (tp, up, size, ap, an);

  size += an;

  if (usize > 0)
    {


      ASSERT_NOCARRY (mpn_sub (tp, tp, size, gp, gn));
      MPN_NORMALIZE (tp, size);
      if (size == 0)
	return 0;
    }
  else
    {


      ASSERT_NOCARRY (mpn_add (tp, tp, size, gp, gn));
      size -= (tp[size - 1] == 0);
    }


  bn = n;
  MPN_NORMALIZE (bp, bn);
  ASSERT (size >= bn);

  vn = size + 1 - bn;
  ASSERT (vn <= n + 1);

  mpn_divexact (vp, tp, size, bp, bn);
  vn -= (vp[vn-1] == 0);

  return vn;
}
