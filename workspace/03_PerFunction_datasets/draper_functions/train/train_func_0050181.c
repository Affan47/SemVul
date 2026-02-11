core_environments_unobserve (SCM env, SCM observer)
{
  unsigned int handling_weaks;
  for (handling_weaks = 0; handling_weaks <= 1; ++handling_weaks)
    {
      SCM l = handling_weaks
	? CORE_ENVIRONMENT_WEAK_OBSERVERS (env)
	: CORE_ENVIRONMENT_OBSERVERS (env);

      if (!scm_is_null (l))
	{
	  SCM rest = SCM_CDR (l);
	  SCM first = handling_weaks
	    ? SCM_CDAR (l)
	    : SCM_CAR (l);

	  if (scm_is_eq (first, observer))
	    {

	      if (handling_weaks)
		SCM_SET_CORE_ENVIRONMENT_WEAK_OBSERVERS (env, rest);
              else
                SCM_SET_CORE_ENVIRONMENT_OBSERVERS (env, rest);
	      return;
	    }

	  do {
	    SCM rest = SCM_CDR (l);

	    if (!scm_is_null (rest))
	      {
		SCM next = handling_weaks
		  ? SCM_CDAR (l)
		  : SCM_CAR (l);

		if (scm_is_eq (next, observer))
		  {
		    SCM_SETCDR (l, SCM_CDR (rest));
		    return;
		  }
	      }

	    l = rest;
	  } while (!scm_is_null (l));
	}
    }


}
