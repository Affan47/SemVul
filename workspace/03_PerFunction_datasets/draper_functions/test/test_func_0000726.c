rewrite_update_phi_arguments (basic_block bb)
{
  edge e;
  edge_iterator ei;
  unsigned i;

  FOR_EACH_EDGE (e, ei, bb->succs)
    {
      gimple phi;
      gimple_vec phis;

      if (!bitmap_bit_p (blocks_with_phis_to_rewrite, e->dest->index))
	continue;

      phis = phis_to_rewrite[e->dest->index];
      FOR_EACH_VEC_ELT (phis, i, phi)
	{
	  tree arg, lhs_sym, reaching_def = NULL;
	  use_operand_p arg_p;

  	  gcc_checking_assert (rewrite_uses_p (phi));

	  arg_p = PHI_ARG_DEF_PTR_FROM_EDGE (phi, e);
	  arg = USE_FROM_PTR (arg_p);

	  if (arg && !DECL_P (arg) && TREE_CODE (arg) != SSA_NAME)
	    continue;

	  lhs_sym = SSA_NAME_VAR (gimple_phi_result (phi));

	  if (arg == NULL_TREE)
	    {


	      reaching_def = get_reaching_def (lhs_sym);

	    }
	  else
	    {
	      tree sym = DECL_P (arg) ? arg : SSA_NAME_VAR (arg);

	      if (marked_for_renaming (sym))
		reaching_def = get_reaching_def (sym);
	      else if (is_old_name (arg))
		reaching_def = get_reaching_def (arg);
	    }


	  if (reaching_def)
	    {
	      source_location locus;
	      int arg_i = PHI_ARG_INDEX_FROM_USE (arg_p);

	      SET_USE (arg_p, reaching_def);


	      if (virtual_operand_p (reaching_def))
		locus = UNKNOWN_LOCATION;
	      else
		{
		  gimple stmt = SSA_NAME_DEF_STMT (reaching_def);


		  if (gimple_code (stmt) == GIMPLE_PHI
		      && gimple_phi_num_args (stmt) == 1)
		    locus = gimple_phi_arg_location (stmt, 0);
		  else
		    locus = gimple_location (stmt);
		}

	      gimple_phi_arg_set_location (phi, arg_i, locus);
	    }


	  if (e->flags & EDGE_ABNORMAL)
	    SSA_NAME_OCCURS_IN_ABNORMAL_PHI (USE_FROM_PTR (arg_p)) = 1;
	}
    }
}
