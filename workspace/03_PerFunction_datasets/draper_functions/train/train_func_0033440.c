get_continuation_for_phi (gimple phi, ao_ref *ref, bitmap *visited)
{
  unsigned nargs = gimple_phi_num_args (phi);


  if (nargs == 1)
    return PHI_ARG_DEF (phi, 0);


  if (nargs == 2)
    {
      tree arg0 = PHI_ARG_DEF (phi, 0);
      tree arg1 = PHI_ARG_DEF (phi, 1);
      gimple def0 = SSA_NAME_DEF_STMT (arg0);
      gimple def1 = SSA_NAME_DEF_STMT (arg1);
      tree common_vuse;

      if (arg0 == arg1)
	return arg0;
      else if (gimple_nop_p (def0)
	       || (!gimple_nop_p (def1)
		   && dominated_by_p (CDI_DOMINATORS,
				      gimple_bb (def1), gimple_bb (def0))))
	{
	  if (maybe_skip_until (phi, arg0, ref, arg1, visited))
	    return arg0;
	}
      else if (gimple_nop_p (def1)
	       || dominated_by_p (CDI_DOMINATORS,
				  gimple_bb (def0), gimple_bb (def1)))
	{
	  if (maybe_skip_until (phi, arg1, ref, arg0, visited))
	    return arg1;
	}


      else if ((common_vuse = gimple_vuse (def0))
	       && common_vuse == gimple_vuse (def1))
	{
	  if (!stmt_may_clobber_ref_p_1 (def0, ref)
	      && !stmt_may_clobber_ref_p_1 (def1, ref))
	    return common_vuse;
	}
    }

  return NULL_TREE;
}
