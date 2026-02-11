gcl_isnormal_double(double d) {

  union {double d;int i[2];} u;

  if (!ISFINITE(d) || !d)
    return 0;

  u.d = d;
  return (u.i[HIND] & 0x7ff00000) != 0;

}
