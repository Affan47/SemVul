connect_infinite_loops_to_exit (void)
{
  basic_block unvisited_block = EXIT_BLOCK_PTR;
  basic_block deadend_block;
  struct depth_first_search_dsS dfs_ds;


  flow_dfs_compute_reverse_init (&dfs_ds);
  flow_dfs_compute_reverse_add_bb (&dfs_ds, EXIT_BLOCK_PTR);


  while (1)
    {
      unvisited_block = flow_dfs_compute_reverse_execute (&dfs_ds,
							  unvisited_block);
      if (!unvisited_block)
	break;

      deadend_block = dfs_find_deadend (unvisited_block);
      make_edge (deadend_block, EXIT_BLOCK_PTR, EDGE_FAKE);
      flow_dfs_compute_reverse_add_bb (&dfs_ds, deadend_block);
    }

  flow_dfs_compute_reverse_finish (&dfs_ds);
  return;
}
