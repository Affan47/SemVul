compute_split_row (sbitmap sched_nodes, int low, int up, int ii,
		   ddg_node_ptr u_node)
{
  ddg_edge_ptr e;
  int lower = INT_MIN, upper = INT_MAX;
  int crit_pred = -1;
  int crit_succ = -1;
  int crit_cycle;

  for (e = u_node->in; e != 0; e = e->next_in)
    {
      int v = e->src->cuid;

      if (bitmap_bit_p (sched_nodes, v)
	  && (low == SCHED_TIME (v) + e->latency - (e->distance * ii)))
	if (SCHED_TIME (v) > lower)
	  {
	    crit_pred = v;
	    lower = SCHED_TIME (v);
	  }
    }

  if (crit_pred >= 0)
    {
      crit_cycle = SCHED_TIME (crit_pred) + 1;
      return SMODULO (crit_cycle, ii);
    }

  for (e = u_node->out; e != 0; e = e->next_out)
    {
      int v = e->dest->cuid;

      if (bitmap_bit_p (sched_nodes, v)
	  && (up == SCHED_TIME (v) - e->latency + (e->distance * ii)))
	if (SCHED_TIME (v) < upper)
	  {
	    crit_succ = v;
	    upper = SCHED_TIME (v);
	  }
    }

  if (crit_succ >= 0)
    {
      crit_cycle = SCHED_TIME (crit_succ);
      return SMODULO (crit_cycle, ii);
    }

  if (dump_file)
    fprintf (dump_file, "Both crit_pred and crit_succ are NULL\n");

  return SMODULO ((low + up + 1) / 2, ii);
}
