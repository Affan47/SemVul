dom_opt_enter_block (struct dom_walk_data *walk_data ATTRIBUTE_UNUSED,
		     basic_block bb)
{
  gimple_stmt_iterator gsi;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "\n\nOptimizing block #%d\n\n", bb->index);


  VEC_safe_push (expr_hash_elt_t, heap, avail_exprs_stack, NULL);
  VEC_safe_push (tree, heap, const_and_copies_stack, NULL_TREE);

  record_equivalences_from_incoming_edge (bb);


  record_equivalences_from_phis (bb);


  VEC_safe_push (expr_hash_elt_t, heap, avail_exprs_stack, NULL);
  for (gsi = gsi_start_phis (bb); !gsi_end_p (gsi); gsi_next (&gsi))
    eliminate_redundant_computations (&gsi);
  remove_local_expressions_from_table ();

  for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
    optimize_stmt (bb, gsi);


  record_edge_info (bb);
  cprop_into_successor_phis (bb);
}
