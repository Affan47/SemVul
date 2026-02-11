mpfr_set_prec (mpfr_ptr x, mpfr_prec_t p)
{
  mp_size_t xsize, xoldsize;
  mpfr_limb_ptr tmp;


  MPFR_ASSERTN (p >= MPFR_PREC_MIN && p <= MPFR_PREC_MAX);


  xsize = MPFR_PREC2LIMBS (p);


  xoldsize = MPFR_GET_ALLOC_SIZE (x);
  if (xsize > xoldsize)
    {
      tmp = (mpfr_limb_ptr) (*__gmp_reallocate_func)
        (MPFR_GET_REAL_PTR(x), MPFR_MALLOC_SIZE(xoldsize), MPFR_MALLOC_SIZE(xsize));
      MPFR_SET_MANT_PTR(x, tmp);
      MPFR_SET_ALLOC_SIZE(x, xsize);
    }
  MPFR_PREC (x) = p;
  MPFR_SET_NAN (x);
}
