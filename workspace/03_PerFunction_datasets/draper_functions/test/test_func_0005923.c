more_one_region_p (void)
{
  unsigned int i;
  loop_p loop;

  FOR_EACH_VEC_ELT (loop_p, ira_loops.larray, i, loop)
    if (ira_loop_nodes[i].regno_allocno_map != NULL
	&& ira_loop_tree_root != &ira_loop_nodes[i])
      return true;
  return false;
}
