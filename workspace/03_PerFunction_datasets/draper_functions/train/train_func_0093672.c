combine_cond_exprs (gimple_stmt_iterator *gsi_p)
{
  gimple stmt = gsi_stmt (*gsi_p);
  tree cond, val1, val2;
  bool changed = false;

  cond = gimple_assign_rhs1 (stmt);
  val1 = gimple_assign_rhs2 (stmt);
  if (TREE_CODE (val1) == SSA_NAME)
    {
      gimple def_stmt = SSA_NAME_DEF_STMT (val1);
      if (is_gimple_assign (def_stmt)
	  && gimple_assign_rhs_code (def_stmt) == gimple_assign_rhs_code (stmt)
	  && operand_equal_p (gimple_assign_rhs1 (def_stmt), cond, 0))
	{
	  val1 = unshare_expr (gimple_assign_rhs2 (def_stmt));
	  gimple_assign_set_rhs2 (stmt, val1);
	  changed = true;
	}
    }
  val2 = gimple_assign_rhs3 (stmt);
  if (TREE_CODE (val2) == SSA_NAME)
    {
      gimple def_stmt = SSA_NAME_DEF_STMT (val2);
      if (is_gimple_assign (def_stmt)
	  && gimple_assign_rhs_code (def_stmt) == gimple_assign_rhs_code (stmt)
	  && operand_equal_p (gimple_assign_rhs1 (def_stmt), cond, 0))
	{
	  val2 = unshare_expr (gimple_assign_rhs3 (def_stmt));
	  gimple_assign_set_rhs3 (stmt, val2);
	  changed = true;
	}
    }
  if (operand_equal_p (val1, val2, 0))
    {
      gimple_assign_set_rhs_from_tree (gsi_p, val1);
      stmt = gsi_stmt (*gsi_p);
      changed = true;
    }

  if (changed)
    update_stmt (stmt);

  return changed;
}
