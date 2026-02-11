eliminate_local_variables (edge entry, edge exit)
{
  basic_block bb;
  VEC (basic_block, heap) *body = VEC_alloc (basic_block, heap, 3);
  unsigned i;
  gimple_stmt_iterator gsi;
  bool has_debug_stmt = false;
  htab_t decl_address = htab_create (10, int_tree_map_hash, int_tree_map_eq,
				     free);
  basic_block entry_bb = entry->src;
  basic_block exit_bb = exit->dest;

  gather_blocks_in_sese_region (entry_bb, exit_bb, &body);

  FOR_EACH_VEC_ELT (basic_block, body, i, bb)
    if (bb != entry_bb && bb != exit_bb)
      for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	if (gimple_debug_bind_p (gsi_stmt (gsi)))
	  has_debug_stmt = true;
	else
	  eliminate_local_variables_stmt (entry, &gsi, decl_address);

  if (has_debug_stmt)
    FOR_EACH_VEC_ELT (basic_block, body, i, bb)
      if (bb != entry_bb && bb != exit_bb)
	for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	  if (gimple_debug_bind_p (gsi_stmt (gsi)))
	    eliminate_local_variables_stmt (entry, &gsi, decl_address);

  htab_delete (decl_address);
  VEC_free (basic_block, heap, body);
}
