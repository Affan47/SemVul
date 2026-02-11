notify_dependents_of_resolved_value (variable ivar, htab_t vars)
{
  loc_exp_dep *led, *next;

  for (led = VAR_LOC_DEP_LST (ivar); led; led = next)
    {
      decl_or_value dv = led->dv;
      variable var;

      next = led->next;

      if (dv_is_value_p (dv))
	{
	  rtx value = dv_as_value (dv);


	  if (!VALUE_RECURSED_INTO (value))
	    continue;


	  gcc_checking_assert (NO_LOC_P (value));


	  NO_LOC_P (value) = false;
	  VALUE_RECURSED_INTO (value) = false;

	  gcc_checking_assert (dv_changed_p (dv));
	}
      else if (!dv_changed_p (dv))
	continue;

      var = (variable) htab_find_with_hash (vars, dv, dv_htab_hash (dv));

      if (!var)
	var = variable_from_dropped (dv, NO_INSERT);

      if (var)
	notify_dependents_of_resolved_value (var, vars);

      if (next)
	next->pprev = led->pprev;
      if (led->pprev)
	*led->pprev = next;
      led->next = NULL;
      led->pprev = NULL;
    }
}
