set_location_for_edge (edge e)
{
  if (e->goto_locus)
    {
      set_curr_insn_location (e->goto_locus);
    }
  else
    {
      basic_block bb = e->src;
      gimple_stmt_iterator gsi;

      do
	{
	  for (gsi = gsi_last_bb (bb); !gsi_end_p (gsi); gsi_prev (&gsi))
	    {
	      gimple stmt = gsi_stmt (gsi);
	      if (is_gimple_debug (stmt))
		continue;
	      if (gimple_has_location (stmt) || gimple_block (stmt))
		{
		  set_curr_insn_location (gimple_location (stmt));
		  return;
		}
	    }


	  if (single_pred_p (bb))
	    bb = single_pred (bb);
	  else
	    bb = e->src;
	}
      while (bb != e->src);
    }
}
