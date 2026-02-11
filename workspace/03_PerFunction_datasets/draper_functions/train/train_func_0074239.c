return_mpfr (mpfr_ptr x, char *old_stack)
{
  void *mantissa       = mpfr_custom_get_significand (x);
  size_t size_mantissa = mpfr_custom_get_size (mpfr_get_prec (x));
  mpfr_ptr newx;

  memmove (old_stack, x, sizeof (mpfr_t));
  memmove (old_stack + ALIGNED (sizeof (mpfr_t)), mantissa, size_mantissa);
  newx = (mpfr_ptr) old_stack;
  mpfr_custom_move (newx, old_stack + ALIGNED (sizeof (mpfr_t)));
  stack = old_stack + ALIGNED (sizeof (mpfr_t)) + ALIGNED (size_mantissa);
  return newx;
}
