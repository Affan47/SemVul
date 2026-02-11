remove_exits_and_undefined_stmts (struct loop *loop, unsigned int npeeled)
{
  struct nb_iter_bound *elt;
  bool changed = false;

  for (elt = loop->bounds; elt; elt = elt->next)
    {


      if (!elt->is_exit
	  && elt->bound.ult (double_int::from_uhwi (npeeled)))
	{
	  gimple_stmt_iterator gsi = gsi_for_stmt (elt->stmt);
	  gimple stmt = gimple_build_call
	      (builtin_decl_implicit (BUILT_IN_UNREACHABLE), 0);

	  gimple_set_location (stmt, gimple_location (elt->stmt));
	  gsi_insert_before (&gsi, stmt, GSI_NEW_STMT);
	  changed = true;
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "Forced statement unreachable: ");
	      print_gimple_stmt (dump_file, elt->stmt, 0, 0);
	    }
	}

      else if (elt->is_exit
	       && elt->bound.ule (double_int::from_uhwi (npeeled)))
	{
	  basic_block bb = gimple_bb (elt->stmt);
	  edge exit_edge = EDGE_SUCC (bb, 0);

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "Forced exit to be taken: ");
	      print_gimple_stmt (dump_file, elt->stmt, 0, 0);
	    }
	  if (!loop_exit_edge_p (loop, exit_edge))
	    exit_edge = EDGE_SUCC (bb, 1);
	  gcc_checking_assert (loop_exit_edge_p (loop, exit_edge));
	  if (exit_edge->flags & EDGE_TRUE_VALUE)
	    gimple_cond_make_true (elt->stmt);
	  else
	    gimple_cond_make_false (elt->stmt);
	  update_stmt (elt->stmt);
	  changed = true;
	}
    }
  return changed;
}
