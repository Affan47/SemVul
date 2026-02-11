intersect_loc_chains (rtx val, location_chain *dest, struct dfset_merge *dsm,
		      location_chain s1node, variable s2var)
{
  dataflow_set *s1set = dsm->cur;
  dataflow_set *s2set = dsm->src;
  location_chain found;

  if (s2var)
    {
      location_chain s2node;

      gcc_checking_assert (s2var->onepart);

      if (s2var->n_var_parts)
	{
	  s2node = s2var->var_part[0].loc_chain;

	  for (; s1node && s2node;
	       s1node = s1node->next, s2node = s2node->next)
	    if (s1node->loc != s2node->loc)
	      break;
	    else if (s1node->loc == val)
	      continue;
	    else
	      insert_into_intersection (dest, s1node->loc,
					MIN (s1node->init, s2node->init));
	}
    }

  for (; s1node; s1node = s1node->next)
    {
      if (s1node->loc == val)
	continue;

      if ((found = find_loc_in_1pdv (s1node->loc, s2var,
				     shared_hash_htab (s2set->vars))))
	{
	  insert_into_intersection (dest, s1node->loc,
				    MIN (s1node->init, found->init));
	  continue;
	}

      if (GET_CODE (s1node->loc) == VALUE
	  && !VALUE_RECURSED_INTO (s1node->loc))
	{
	  decl_or_value dv = dv_from_value (s1node->loc);
	  variable svar = shared_hash_find (s1set->vars, dv);
	  if (svar)
	    {
	      if (svar->n_var_parts == 1)
		{
		  VALUE_RECURSED_INTO (s1node->loc) = true;
		  intersect_loc_chains (val, dest, dsm,
					svar->var_part[0].loc_chain,
					s2var);
		  VALUE_RECURSED_INTO (s1node->loc) = false;
		}
	    }
	}


    }
}
