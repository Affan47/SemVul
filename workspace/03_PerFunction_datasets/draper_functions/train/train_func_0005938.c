ssa_propagate (ssa_prop_visit_stmt_fn visit_stmt,
	       ssa_prop_visit_phi_fn visit_phi)
{
  ssa_prop_visit_stmt = visit_stmt;
  ssa_prop_visit_phi = visit_phi;

  ssa_prop_init ();


  while (!cfg_blocks_empty_p ()
	 || VEC_length (gimple, interesting_ssa_edges) > 0
	 || VEC_length (gimple, varying_ssa_edges) > 0)
    {
      if (!cfg_blocks_empty_p ())
	{

	  basic_block dest_block = cfg_blocks_get ();
	  simulate_block (dest_block);
	}


      process_ssa_edge_worklist (&varying_ssa_edges);


      process_ssa_edge_worklist (&interesting_ssa_edges);
    }

  ssa_prop_fini ();
}
