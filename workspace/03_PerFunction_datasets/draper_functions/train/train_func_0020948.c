dse_optimize_stmt (gimple_stmt_iterator *gsi)
{
  gimple stmt = gsi_stmt (*gsi);


  if (!gimple_vdef (stmt))
    return;


  if (is_gimple_call (stmt) && gimple_call_fndecl (stmt))
    return;

  if (gimple_has_volatile_ops (stmt))
    return;

  if (is_gimple_assign (stmt))
    {
      gimple use_stmt;

      if (!dse_possible_dead_store_p (stmt, &use_stmt))
	return;


      if ((gimple_has_lhs (use_stmt)
	   && (operand_equal_p (gimple_assign_lhs (stmt),
				gimple_get_lhs (use_stmt), 0)))
	  || stmt_kills_ref_p (use_stmt, gimple_assign_lhs (stmt)))
	{
	  basic_block bb;


	  if (stmt != use_stmt
	      && ref_maybe_used_by_stmt_p (use_stmt, gimple_assign_lhs (stmt)))
	    return;

	  if (dump_file && (dump_flags & TDF_DETAILS))
            {
              fprintf (dump_file, "  Deleted dead store '");
              print_gimple_stmt (dump_file, gsi_stmt (*gsi), dump_flags, 0);
              fprintf (dump_file, "'\n");
            }


	  unlink_stmt_vdef (stmt);


	  bb = gimple_bb (stmt);
	  if (gsi_remove (gsi, true))
	    bitmap_set_bit (need_eh_cleanup, bb->index);


	  release_defs (stmt);
	}
    }
}
