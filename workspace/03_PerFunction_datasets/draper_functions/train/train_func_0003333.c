initialize_parameter_reductions (void)
{
  gimple_stmt_iterator gsi;
  gimple_seq seq = NULL;
  tree parm;

  for (parm = DECL_ARGUMENTS (current_function_decl);
       parm;
       parm = DECL_CHAIN (parm))
    {
      VEC (access_p, heap) *access_vec;
      struct access *access;

      if (!bitmap_bit_p (candidate_bitmap, DECL_UID (parm)))
	continue;
      access_vec = get_base_access_vector (parm);
      if (!access_vec)
	continue;

      if (!seq)
	{
	  seq = gimple_seq_alloc ();
	  gsi = gsi_start (seq);
	}

      for (access = VEC_index (access_p, access_vec, 0);
	   access;
	   access = access->next_grp)
	generate_subtree_copies (access, parm, 0, 0, 0, &gsi, true, true,
				 EXPR_LOCATION (parm));
    }

  if (seq)
    gsi_insert_seq_on_edge_immediate (single_succ_edge (ENTRY_BLOCK_PTR), seq);
}
