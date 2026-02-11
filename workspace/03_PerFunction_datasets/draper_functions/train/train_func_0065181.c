import_environment_lookup (SCM env, SCM sym)
{
  SCM imports = IMPORT_ENVIRONMENT (env)->imports;
  SCM result = SCM_UNDEFINED;
  SCM l;

  for (l = imports; !scm_is_null (l); l = SCM_CDR (l))
    {
      SCM imported = SCM_CAR (l);

      if (SCM_ENVIRONMENT_BOUND_P (imported, sym))
	{
	  if (SCM_UNBNDP (result))
	    result = imported;
	  else if (scm_is_pair (result))
	    result = scm_cons (imported, result);
	  else
	    result = scm_cons2 (imported, result, SCM_EOL);
	}
    }

  if (scm_is_pair (result))
    return scm_reverse (result);
  else
    return result;
}
