gather_caller_stats (struct cgraph_node *node, void *data)
{
  struct caller_statistics *stats = (struct caller_statistics *) data;
  struct cgraph_edge *cs;

  for (cs = node->callers; cs; cs = cs->next_caller)
    if (cs->caller->thunk.thunk_p)
      cgraph_for_node_and_aliases (cs->caller, gather_caller_stats,
				   stats, false);
    else
      {
	stats->count_sum += cs->count;
	stats->freq_sum += cs->frequency;
	stats->n_calls++;
	if (cgraph_maybe_hot_edge_p (cs))
	  stats->n_hot_calls ++;
      }
  return false;

}
