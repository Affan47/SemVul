sbb (mp_limb_t *w, mp_limb_t x, mp_limb_t y, mp_limb_t c)
{
  mp_limb_t  r;

  ASSERT_LIMB (x);
  ASSERT_LIMB (y);
  ASSERT (c == 0 || c == 1);

  r = ref_subc_limb (w, x, y);
  return r + ref_subc_limb (w, *w, c);
}
