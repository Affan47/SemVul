ramap_1 (SCM ra0, SCM proc, SCM ras)
{
  SCM ra1 = SCM_CAR (ras);
  long n = SCM_I_ARRAY_DIMS (ra0)->ubnd - SCM_I_ARRAY_DIMS (ra0)->lbnd + 1;
  unsigned long i0 = SCM_I_ARRAY_BASE (ra0), i1 = SCM_I_ARRAY_BASE (ra1);
  long inc0 = SCM_I_ARRAY_DIMS (ra0)->inc, inc1 = SCM_I_ARRAY_DIMS (ra1)->inc;
  ra0 = SCM_I_ARRAY_V (ra0);
  ra1 = SCM_I_ARRAY_V (ra1);
  if (scm_tc7_vector == SCM_TYP7 (ra0) || scm_tc7_wvect == SCM_TYP7 (ra0))
    for (; n-- > 0; i0 += inc0, i1 += inc1)
      GVSET (ra0, i0, SCM_SUBRF (proc) (GVREF (ra1, i1)));
  else
    for (; n-- > 0; i0 += inc0, i1 += inc1)
      GVSET (ra0, i0, SCM_SUBRF (proc) (GVREF (ra1, i1)));
  return 1;
}
