warn_uninitialized_vars (bool warn_possibly_uninitialized)
{
  gimple_stmt_iterator gsi;
  basic_block bb;

  FOR_EACH_BB (bb)
    {
      bool always_executed = dominated_by_p (CDI_POST_DOMINATORS,
					     single_succ (ENTRY_BLOCK_PTR), bb);
      for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	{
	  gimple stmt = gsi_stmt (gsi);
	  use_operand_p use_p;
	  ssa_op_iter op_iter;
	  tree use;

	  if (is_gimple_debug (stmt))
	    continue;


	  FOR_EACH_SSA_USE_OPERAND (use_p, stmt, op_iter, SSA_OP_USE)
	    {
	      use = USE_FROM_PTR (use_p);
	      if (always_executed)
		warn_uninit (OPT_Wuninitialized, use,
			     SSA_NAME_VAR (use), SSA_NAME_VAR (use),
			     "%qD is used uninitialized in this function",
			     stmt);
	      else if (warn_possibly_uninitialized)
		warn_uninit (OPT_Wmaybe_uninitialized, use,
			     SSA_NAME_VAR (use), SSA_NAME_VAR (use),
			     "%qD may be used uninitialized in this function",
			     stmt);
	    }


	  use = gimple_vuse (stmt);
	  if (use
	      && gimple_assign_single_p (stmt)
	      && !gimple_vdef (stmt)
	      && SSA_NAME_IS_DEFAULT_DEF (use))
	    {
	      tree rhs = gimple_assign_rhs1 (stmt);
	      tree base = get_base_address (rhs);


	      if (TREE_CODE (base) != VAR_DECL
		  || DECL_HARD_REGISTER (base)
		  || is_global_var (base))
		continue;

	      if (always_executed)
		warn_uninit (OPT_Wuninitialized, use,
			     gimple_assign_rhs1 (stmt), base,
			     "%qE is used uninitialized in this function",
			     stmt);
	      else if (warn_possibly_uninitialized)
		warn_uninit (OPT_Wmaybe_uninitialized, use,
			     gimple_assign_rhs1 (stmt), base,
			     "%qE may be used uninitialized in this function",
			     stmt);
	    }
	}
    }

  return 0;
}
