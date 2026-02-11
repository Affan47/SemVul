gh_scm2longs (SCM obj, long *m)
{
  long i, n;
  SCM val;
  if (SCM_IMP (obj))
    scm_wrong_type_arg (0, 0, obj);

  SCM2WHATEVER (obj, scm_s32vector_p, scm_t_int32, long)

  switch (SCM_TYP7 (obj))
    {
    case scm_tc7_vector:
    case scm_tc7_wvect:
      n = SCM_SIMPLE_VECTOR_LENGTH (obj);
      for (i = 0; i < n; ++i)
	{
	  val = SCM_SIMPLE_VECTOR_REF (obj, i);
	  if (!SCM_I_INUMP (val) && !SCM_BIGP (val))
	    scm_wrong_type_arg (0, 0, obj);
	}
      if (m == 0)
	m = (long *) malloc (n * sizeof (long));
      if (m == NULL)
	return NULL;
      for (i = 0; i < n; ++i)
	{
	  val = SCM_SIMPLE_VECTOR_REF (obj, i);
	  m[i] = SCM_I_INUMP (val)
	    ? SCM_I_INUM (val)
	    : scm_to_long (val);
	}
      break;
    default:
      scm_wrong_type_arg (0, 0, obj);
    }
  return m;
}
