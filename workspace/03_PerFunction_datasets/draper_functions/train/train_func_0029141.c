mark_loops_for_removal (void)
{
  int i, n;
  ira_loop_tree_node_t *sorted_loops;
  loop_p loop;

  ira_assert (current_loops != NULL);
  sorted_loops
    = (ira_loop_tree_node_t *) ira_allocate (sizeof (ira_loop_tree_node_t)
					     * number_of_loops ());
  for (n = i = 0; vec_safe_iterate (get_loops (), i, &loop); i++)
    if (ira_loop_nodes[i].regno_allocno_map != NULL)
      {
	if (ira_loop_nodes[i].parent == NULL)
	  {

	    ira_loop_nodes[i].to_remove_p = false;
	    continue;
	  }
	sorted_loops[n++] = &ira_loop_nodes[i];
	ira_loop_nodes[i].to_remove_p
	  = ((low_pressure_loop_node_p (ira_loop_nodes[i].parent)
	      && low_pressure_loop_node_p (&ira_loop_nodes[i]))
#ifdef STACK_REGS
	     || loop_with_complex_edge_p (ira_loop_nodes[i].loop)
#endif
	     );
      }
  qsort (sorted_loops, n, sizeof (ira_loop_tree_node_t), loop_compare_func);
  for (i = 0; n - i + 1 > IRA_MAX_LOOPS_NUM; i++)
    {
      sorted_loops[i]->to_remove_p = true;
      if (internal_flag_ira_verbose > 1 && ira_dump_file != NULL)
	fprintf
	  (ira_dump_file,
	   "  Mark loop %d (header %d, freq %d, depth %d) for removal (%s)\n",
	   sorted_loops[i]->loop_num, sorted_loops[i]->loop->header->index,
	   sorted_loops[i]->loop->header->frequency,
	   loop_depth (sorted_loops[i]->loop),
	   low_pressure_loop_node_p (sorted_loops[i]->parent)
	   && low_pressure_loop_node_p (sorted_loops[i])
	   ? "low pressure" : "cheap loop");
    }
  ira_free (sorted_loops);
}
