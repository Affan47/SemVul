calculate_live_on_exit (tree_live_info_p liveinfo)
{
  basic_block bb;
  edge e;
  edge_iterator ei;


  FOR_EACH_BB (bb)
    bitmap_clear (liveinfo->liveout[bb->index]);


  FOR_EACH_BB (bb)
    {
      gimple_stmt_iterator gsi;
      size_t i;


      for (gsi = gsi_start_phis (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	{
	  gimple phi = gsi_stmt (gsi);
	  for (i = 0; i < gimple_phi_num_args (phi); i++)
	    {
	      tree t = PHI_ARG_DEF (phi, i);
	      int p;

	      if (TREE_CODE (t) != SSA_NAME)
		continue;

	      p = var_to_partition (liveinfo->map, t);
	      if (p == NO_PARTITION)
		continue;
	      e = gimple_phi_arg_edge (phi, i);
	      if (e->src != ENTRY_BLOCK_PTR)
		bitmap_set_bit (liveinfo->liveout[e->src->index], p);
	    }
	}


      FOR_EACH_EDGE (e, ei, bb->succs)
        if (e->dest != EXIT_BLOCK_PTR)
	  bitmap_ior_into (liveinfo->liveout[bb->index],
			   live_on_entry (liveinfo, e->dest));
    }
}
