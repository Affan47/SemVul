write_memrefs_written_at_least_once (gimple stmt,
				     VEC (data_reference_p, heap) *drs)
{
  int i, j;
  data_reference_p a, b;
  tree ca = bb_predicate (gimple_bb (stmt));

  for (i = 0; VEC_iterate (data_reference_p, drs, i, a); i++)
    if (DR_STMT (a) == stmt
	&& DR_IS_WRITE (a))
      {
	bool found = false;
	int x = DR_WRITTEN_AT_LEAST_ONCE (a);

	if (x == 0)
	  return false;

	if (x == 1)
	  continue;

	for (j = 0; VEC_iterate (data_reference_p, drs, j, b); j++)
	  if (DR_STMT (b) != stmt
	      && DR_IS_WRITE (b)
	      && same_data_refs_base_objects (a, b))
	    {
	      tree cb = bb_predicate (gimple_bb (DR_STMT (b)));

	      if (DR_WRITTEN_AT_LEAST_ONCE (b) == 1
		  || is_true_predicate (cb)
		  || is_true_predicate (ca = fold_or_predicates (EXPR_LOCATION (cb),
								 ca, cb)))
		{
		  DR_WRITTEN_AT_LEAST_ONCE (a) = 1;
		  DR_WRITTEN_AT_LEAST_ONCE (b) = 1;
		  found = true;
		  break;
		}
	    }

	if (!found)
	  {
	    DR_WRITTEN_AT_LEAST_ONCE (a) = 0;
	    return false;
	  }
      }

  return true;
}
