convert_callers (struct cgraph_node *node, tree old_decl,
		 ipa_parm_adjustment_vec adjustments)
{
  tree old_cur_fndecl = current_function_decl;
  basic_block this_block;

  cgraph_for_node_and_aliases (node, convert_callers_for_node,
			       adjustments, false);

  current_function_decl = old_cur_fndecl;

  if (!encountered_recursive_call)
    return;

  FOR_EACH_BB (this_block)
    {
      gimple_stmt_iterator gsi;

      for (gsi = gsi_start_bb (this_block); !gsi_end_p (gsi); gsi_next (&gsi))
        {
	  gimple stmt = gsi_stmt (gsi);
	  tree call_fndecl;
	  if (gimple_code (stmt) != GIMPLE_CALL)
	    continue;
	  call_fndecl = gimple_call_fndecl (stmt);
	  if (call_fndecl == old_decl)
	    {
	      if (dump_file)
		fprintf (dump_file, "Adjusting recursive call");
	      gimple_call_set_fndecl (stmt, node->decl);
	      ipa_modify_call_arguments (NULL, stmt, adjustments);
	    }
	}
    }

  return;
}
