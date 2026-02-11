ref_subc_limb (mp_limb_t *w, mp_limb_t x, mp_limb_t y)
{
  mp_limb_t  diff, cy;

  ASSERT_LIMB (x);
  ASSERT_LIMB (y);

  diff = x - y;
#if GMP_NAIL_BITS == 0
  *w = diff;
  cy = (diff > x);
#else
  *w = diff & GMP_NUMB_MASK;
  cy = (diff >> GMP_NUMB_BITS) & 1;
#endif
  return cy;
}
