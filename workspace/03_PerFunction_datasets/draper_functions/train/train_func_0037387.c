propagate_into_all_uses (tree ssa_name, tree val)
{
  imm_use_iterator iter;
  gimple use_stmt;

  FOR_EACH_IMM_USE_STMT (use_stmt, iter, ssa_name)
    {
      gimple_stmt_iterator use_stmt_gsi = gsi_for_stmt (use_stmt);
      use_operand_p use;

      FOR_EACH_IMM_USE_ON_STMT (use, iter)
	SET_USE (use, val);

      if (is_gimple_assign (use_stmt)
	  && get_gimple_rhs_class (gimple_assign_rhs_code (use_stmt))
	     == GIMPLE_SINGLE_RHS)
	{
	  tree rhs = gimple_assign_rhs1 (use_stmt);

	  if (TREE_CODE (rhs) == ADDR_EXPR)
	    recompute_tree_invariant_for_addr_expr (rhs);
	}

      fold_stmt_inplace (&use_stmt_gsi);
      update_stmt (use_stmt);
      maybe_clean_or_replace_eh_stmt (use_stmt, use_stmt);
    }
}
