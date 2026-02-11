init_copy_prop (void)
{
  basic_block bb;

  copy_of = XCNEWVEC (prop_value_t, num_ssa_names);

  FOR_EACH_BB (bb)
    {
      gimple_stmt_iterator si;
      int depth = bb->loop_depth;

      for (si = gsi_start_bb (bb); !gsi_end_p (si); gsi_next (&si))
	{
	  gimple stmt = gsi_stmt (si);
	  ssa_op_iter iter;
          tree def;


	  if (stmt_ends_bb_p (stmt))
            prop_set_simulate_again (stmt, true);
	  else if (stmt_may_generate_copy (stmt)


                   && loop_depth_of_name (gimple_assign_rhs1 (stmt)) <= depth)
            prop_set_simulate_again (stmt, true);
	  else
            prop_set_simulate_again (stmt, false);


	  FOR_EACH_SSA_TREE_OPERAND (def, stmt, iter, SSA_OP_ALL_DEFS)
            if (!prop_simulate_again_p (stmt))
	      set_copy_of_val (def, def);
	}

      for (si = gsi_start_phis (bb); !gsi_end_p (si); gsi_next (&si))
	{
          gimple phi = gsi_stmt (si);
          tree def;

	  def = gimple_phi_result (phi);
	  if (!is_gimple_reg (def))
            prop_set_simulate_again (phi, false);
	  else
            prop_set_simulate_again (phi, true);

	  if (!prop_simulate_again_p (phi))
	    set_copy_of_val (def, def);
	}
    }
}
