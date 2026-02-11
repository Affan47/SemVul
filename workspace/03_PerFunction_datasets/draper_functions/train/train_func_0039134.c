racp (SCM src, SCM dst)
{
  long n = (SCM_I_ARRAY_DIMS (src)->ubnd - SCM_I_ARRAY_DIMS (src)->lbnd + 1);
  long inc_d, inc_s = SCM_I_ARRAY_DIMS (src)->inc;
  unsigned long i_d, i_s = SCM_I_ARRAY_BASE (src);
  dst = SCM_CAR (dst);
  inc_d = SCM_I_ARRAY_DIMS (dst)->inc;
  i_d = SCM_I_ARRAY_BASE (dst);
  src = SCM_I_ARRAY_V (src);
  dst = SCM_I_ARRAY_V (dst);

  for (; n-- > 0; i_s += inc_s, i_d += inc_d)
    GVSET (dst, i_d, GVREF (src, i_s));
  return 1;
}
