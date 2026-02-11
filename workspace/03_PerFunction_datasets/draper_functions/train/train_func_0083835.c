ecm_mod_1 (mp_ptr xp, mp_size_t xn, mp_limb_t p, mp_size_t n,
           mp_limb_t invm, mp_limb_t Bpow)
{
  mp_limb_t q, cy, hi, lo, x0, x1;

  if (xn == 0)
    return 0;


  if (xn > n + 1)
    return mpn_mod_1 (xp, xn, p);

  x0 = xp[0];
  cy = (mp_limb_t) 0;
  while (n-- > 0)
    {

      x1 = (xn > 1) ? xp[1] : 0;
      q = x0 * invm;
      umul_ppmm (hi, lo, q, p);


      hi += cy + (lo != 0);
      x0 = x1 + hi;
      cy = x0 < hi;
      xn --;
      xp ++;
    }
  if (cy != 0)
    x0 -= p;

  umul_ppmm (x1, x0, x0, Bpow);

  q = x0 * invm;
  umul_ppmm (hi, lo, q, p);

  hi = hi + x1 + (lo != 0);
  while (hi >= p)
    hi -= p;
  return hi;
}
