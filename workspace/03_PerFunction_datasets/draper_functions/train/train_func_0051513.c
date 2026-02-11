unify_inconsistency (bool explain_p, tree parm, tree first, tree second)
{
  if (explain_p)
    {
      if (TYPE_P (parm))
	inform (input_location,
		"  deduced conflicting types for parameter %qT (%qT and %qT)",
		parm, first, second);
      else
	inform (input_location,
		"  deduced conflicting values for non-type parameter "
		"%qE (%qE and %qE)", parm, first, second);
    }
  return 1;
}
