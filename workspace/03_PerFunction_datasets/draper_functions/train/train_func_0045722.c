insert_clobbers_for_var (gimple_stmt_iterator i, tree var)
{
  gimple stmt;
  tree saved_val;
  htab_t visited = NULL;

  for (; !gsi_end_p (i); gsi_prev_dom_bb_nondebug (&i))
    {
      stmt = gsi_stmt (i);

      if (!gimple_call_builtin_p (stmt, BUILT_IN_STACK_SAVE))
	continue;

      saved_val = gimple_call_lhs (stmt);
      if (saved_val == NULL_TREE)
	continue;

      insert_clobber_before_stack_restore (saved_val, var, &visited);
      break;
    }

  if (visited != NULL)
    htab_delete (visited);
}
