find_referenced_vars (void)
{
  basic_block bb;
  gimple_stmt_iterator si;

  FOR_EACH_BB (bb)
    {
      for (si = gsi_start_bb (bb); !gsi_end_p (si); gsi_next (&si))
	{
	  gimple stmt = gsi_stmt (si);
	  if (is_gimple_debug (stmt))
	    continue;
	  find_referenced_vars_in (gsi_stmt (si));
	}

      for (si = gsi_start_phis (bb); !gsi_end_p (si); gsi_next (&si))
	find_referenced_vars_in (gsi_stmt (si));
    }

  return 0;
}
