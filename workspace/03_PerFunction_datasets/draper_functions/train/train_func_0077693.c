generate_loops_for_partition (struct loop *loop, bitmap partition, bool copy_p)
{
  unsigned i, x;
  gimple_stmt_iterator bsi;
  basic_block *bbs;

  if (copy_p)
    {
      loop = copy_loop_before (loop);
      create_preheader (loop, CP_SIMPLE_PREHEADERS);
      create_bb_after_loop (loop);
    }

  if (loop == NULL)
    return false;


  bbs = get_loop_body_in_dom_order (loop);

  if (MAY_HAVE_DEBUG_STMTS)
    for (x = 0, i = 0; i < loop->num_nodes; i++)
      {
	basic_block bb = bbs[i];

	for (bsi = gsi_start_phis (bb); !gsi_end_p (bsi); gsi_next (&bsi))
	  if (!bitmap_bit_p (partition, x++))
	    reset_debug_uses (gsi_stmt (bsi));

	for (bsi = gsi_start_bb (bb); !gsi_end_p (bsi); gsi_next (&bsi))
	  {
	    gimple stmt = gsi_stmt (bsi);
	    if (gimple_code (stmt) != GIMPLE_LABEL
		&& !is_gimple_debug (stmt)
		&& !bitmap_bit_p (partition, x++))
	      reset_debug_uses (stmt);
	  }
      }

  for (x = 0, i = 0; i < loop->num_nodes; i++)
    {
      basic_block bb = bbs[i];

      for (bsi = gsi_start_phis (bb); !gsi_end_p (bsi);)
	if (!bitmap_bit_p (partition, x++))
	  {
	    gimple phi = gsi_stmt (bsi);
	    if (!is_gimple_reg (gimple_phi_result (phi)))
	      mark_virtual_phi_result_for_renaming (phi);
	    remove_phi_node (&bsi, true);
	  }
	else
	  gsi_next (&bsi);

      for (bsi = gsi_start_bb (bb); !gsi_end_p (bsi);)
	{
	  gimple stmt = gsi_stmt (bsi);
	  if (gimple_code (stmt) != GIMPLE_LABEL
	      && !is_gimple_debug (stmt)
	      && !bitmap_bit_p (partition, x++))
	    {
	      unlink_stmt_vdef (stmt);
	      gsi_remove (&bsi, true);
	      release_defs (stmt);
	    }
	  else
	    gsi_next (&bsi);
	}
    }

  free (bbs);
  return true;
}
