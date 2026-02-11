scm_ra_divide (SCM ra0, SCM ras)
{
  long n = SCM_I_ARRAY_DIMS (ra0)->ubnd - SCM_I_ARRAY_DIMS (ra0)->lbnd + 1;
  unsigned long i0 = SCM_I_ARRAY_BASE (ra0);
  long inc0 = SCM_I_ARRAY_DIMS (ra0)->inc;
  ra0 = SCM_I_ARRAY_V (ra0);
  if (scm_is_null (ras))
    {
      switch (SCM_TYP7 (ra0))
	{
	default:
	  {
	    for (; n-- > 0; i0 += inc0)
	      GVSET (ra0, i0, scm_divide (GVREF (ra0, i0), SCM_UNDEFINED));
	    break;
	  }
	}
    }
  else
    {
      SCM ra1 = SCM_CAR (ras);
      unsigned long i1 = SCM_I_ARRAY_BASE (ra1);
      long inc1 = SCM_I_ARRAY_DIMS (ra1)->inc;
      ra1 = SCM_I_ARRAY_V (ra1);
      switch (SCM_TYP7 (ra0) == SCM_TYP7 (ra1) ? SCM_TYP7 (ra0) : 0)
	{
	default:
	  {
	    for (; n-- > 0; i0 += inc0, i1 += inc1)
	      {
		SCM res =  scm_divide (GVREF (ra0, i0),
				       GVREF (ra1, i1));
		GVSET (ra0, i0, res);
	      }
	    break;
	  }
	}
    }
  return 1;
}
