rafe (SCM ra0, SCM proc, SCM ras)
{
  long i = SCM_I_ARRAY_DIMS (ra0)->lbnd;
  unsigned long i0 = SCM_I_ARRAY_BASE (ra0);
  long inc0 = SCM_I_ARRAY_DIMS (ra0)->inc;
  long n = SCM_I_ARRAY_DIMS (ra0)->ubnd;
  ra0 = SCM_I_ARRAY_V (ra0);
  if (scm_is_null (ras))
    for (; i <= n; i++, i0 += inc0)
      scm_call_1 (proc, GVREF (ra0, i0));
  else
    {
      SCM ra1 = SCM_CAR (ras);
      SCM args;
      unsigned long k, i1 = SCM_I_ARRAY_BASE (ra1);
      long inc1 = SCM_I_ARRAY_DIMS (ra1)->inc;
      ra1 = SCM_I_ARRAY_V (ra1);
      ras = SCM_CDR (ras);
      if (scm_is_null(ras))
	ras = scm_nullvect;
      else
	ras = scm_vector (ras);
      for (; i <= n; i++, i0 += inc0, i1 += inc1)
	{
	  args = SCM_EOL;
	  for (k = scm_c_vector_length (ras); k--;)
	    args = scm_cons (GVREF (scm_c_vector_ref (ras, k), i), args);
	  args = scm_cons2 (GVREF (ra0, i0), GVREF (ra1, i1), args);
	  scm_apply_0 (proc, args);
	}
    }
  return 1;
}
