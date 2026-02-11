remove_visited_stmt_chain (tree var)
{
  gimple stmt;
  gimple_stmt_iterator gsi;

  while (1)
    {
      if (TREE_CODE (var) != SSA_NAME || !has_zero_uses (var))
	return;
      stmt = SSA_NAME_DEF_STMT (var);
      if (is_gimple_assign (stmt) && gimple_visited_p (stmt))
	{
	  var = gimple_assign_rhs1 (stmt);
	  gsi = gsi_for_stmt (stmt);
	  gsi_remove (&gsi, true);
	  release_defs (stmt);
	}
      else
	return;
    }
}
