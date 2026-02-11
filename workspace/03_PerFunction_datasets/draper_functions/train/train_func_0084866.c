build_cgraph_edges (void)
{
  basic_block bb;
  struct cgraph_node *node = cgraph_node (current_function_decl);
  struct pointer_set_t *visited_nodes = pointer_set_create ();
  gimple_stmt_iterator gsi;
  tree decl;
  unsigned ix;


  FOR_EACH_BB (bb)
    {
      for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	{
	  gimple stmt = gsi_stmt (gsi);
	  tree decl;

	  if (is_gimple_call (stmt))
	    {
	      int freq = compute_call_stmt_bb_frequency (current_function_decl,
							 bb);
	      decl = gimple_call_fndecl (stmt);
	      if (decl)
		cgraph_create_edge (node, cgraph_node (decl), stmt,
				    bb->count, freq,
				    bb->loop_depth);
	      else
		cgraph_create_indirect_edge (node, stmt,
					     gimple_call_flags (stmt),
					     bb->count, freq,
					     bb->loop_depth);
	    }
	  walk_stmt_load_store_addr_ops (stmt, node, mark_load,
					 mark_store, mark_address);
	  if (gimple_code (stmt) == GIMPLE_OMP_PARALLEL
	      && gimple_omp_parallel_child_fn (stmt))
	    {
	      tree fn = gimple_omp_parallel_child_fn (stmt);
	      ipa_record_reference (node, NULL, cgraph_node (fn),
				    NULL, IPA_REF_ADDR, stmt);
	    }
	  if (gimple_code (stmt) == GIMPLE_OMP_TASK)
	    {
	      tree fn = gimple_omp_task_child_fn (stmt);
	      if (fn)
		ipa_record_reference (node, NULL, cgraph_node (fn),
				      NULL, IPA_REF_ADDR, stmt);
	      fn = gimple_omp_task_copy_fn (stmt);
	      if (fn)
		ipa_record_reference (node, NULL, cgraph_node (fn),
				      NULL, IPA_REF_ADDR, stmt);
	    }
	}
      for (gsi = gsi_start (phi_nodes (bb)); !gsi_end_p (gsi); gsi_next (&gsi))
	walk_stmt_load_store_addr_ops (gsi_stmt (gsi), node,
				       mark_load, mark_store, mark_address);
   }


  FOR_EACH_LOCAL_DECL (cfun, ix, decl)
    if (TREE_CODE (decl) == VAR_DECL
	&& (TREE_STATIC (decl) && !DECL_EXTERNAL (decl)))
      varpool_finalize_decl (decl);
  record_eh_tables (node, cfun);

  pointer_set_destroy (visited_nodes);
  return 0;
}
