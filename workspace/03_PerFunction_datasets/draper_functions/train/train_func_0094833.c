gh_scm2floats (SCM obj, float *m)
{
  long i, n;
  SCM val;
  if (SCM_IMP (obj))
    scm_wrong_type_arg (0, 0, obj);


  SCM2WHATEVER (obj, scm_f32vector_p, float, float)

  switch (SCM_TYP7 (obj))
    {
    case scm_tc7_vector:
    case scm_tc7_wvect:
      n = SCM_SIMPLE_VECTOR_LENGTH (obj);
      for (i = 0; i < n; ++i)
	{
	  val = SCM_SIMPLE_VECTOR_REF (obj, i);
	  if (!SCM_I_INUMP (val)
	      && !(SCM_BIGP (val) || SCM_REALP (val)))
	    scm_wrong_type_arg (0, 0, val);
	}
      if (m == 0)
	m = (float *) malloc (n * sizeof (float));
      if (m == NULL)
	return NULL;
      for (i = 0; i < n; ++i)
	{
	  val = SCM_SIMPLE_VECTOR_REF (obj, i);
	  if (SCM_I_INUMP (val))
	    m[i] = SCM_I_INUM (val);
	  else if (SCM_BIGP (val))
	    m[i] = scm_to_long (val);
	  else
	    m[i] = SCM_REAL_VALUE (val);
	}
      break;
    default:
      scm_wrong_type_arg (0, 0, obj);
    }
  return m;
}
