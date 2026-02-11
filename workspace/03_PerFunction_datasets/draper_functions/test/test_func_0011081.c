s_mp_invmod_odd_m(const mp_int *a, const mp_int *m, mp_int *c)
{
  int k;
  mp_err  res;
  mp_int  x;

  ARGCHK(a && m && c, MP_BADARG);

  if(mp_cmp_z(a) == 0 || mp_cmp_z(m) == 0)
    return MP_RANGE;
  if (mp_iseven(m))
    return MP_UNDEF;

  MP_DIGITS(&x) = 0;

  if (a == c) {
    if ((res = mp_init_copy(&x, a)) != MP_OKAY)
      return res;
    if (a == m)
      m = &x;
    a = &x;
  } else if (m == c) {
    if ((res = mp_init_copy(&x, m)) != MP_OKAY)
      return res;
    m = &x;
  } else {
    MP_DIGITS(&x) = 0;
  }

  MP_CHECKOK( s_mp_almost_inverse(a, m, c) );
  k = res;
  MP_CHECKOK( s_mp_fixup_reciprocal(c, m, k, c) );
CLEANUP:
  mp_clear(&x);
  return res;
}
