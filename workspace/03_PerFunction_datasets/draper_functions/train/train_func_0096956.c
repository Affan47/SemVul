mord_2exp (mpz_ptr ldst, mpz_ptr rdst, mpz_srcptr lsrc, mpz_srcptr rsrc,
           mp_bitcnt_t n)
{
  mp_size_t  rsrc_size = SIZ(rsrc);
  mp_size_t  len = ABS (rsrc_size);
  mp_ptr     rsrc_ptr = PTR(rsrc);
  mp_ptr     p, rdst_ptr;
  mp_limb_t  plow;

  p = rsrc_ptr;
  plow = *p;
  while (n >= GMP_NUMB_BITS && plow == 0)
    {
      n -= GMP_NUMB_BITS;
      p++;
      plow = *p;
    }


  len -= (p - rsrc_ptr);
  MPZ_REALLOC (rdst, len);
  rdst_ptr = PTR(rdst);

  if ((plow & 1) || n == 0)
    {

      if (p != rdst_ptr)
        MPN_COPY_DECR (rdst_ptr, p, len);
    }
  else
    {
      unsigned long  shift;
      if (plow == 0)
        shift = n;
      else
        {
          count_trailing_zeros (shift, plow);
          shift = MIN (shift, n);
        }
      mpn_rshift (rdst_ptr, p, len, shift);
      len -= (rdst_ptr[len-1] == 0);
      n -= shift;
    }
  SIZ(rdst) = (rsrc_size >= 0) ? len : -len;

  if (n)
    mpz_mul_2exp (ldst, lsrc, n);
  else if (ldst != lsrc)
    mpz_set (ldst, lsrc);
}
