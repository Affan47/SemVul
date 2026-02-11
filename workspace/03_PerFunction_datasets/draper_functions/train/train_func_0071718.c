propagate_constants_topo (struct topo_info *topo)
{
  int i;

  for (i = topo->nnodes - 1; i >= 0; i--)
    {
      struct cgraph_node *v, *node = topo->order[i];
      struct ipa_dfs_info *node_dfs_info;

      if (!cgraph_function_with_gimple_body_p (node))
	continue;

      node_dfs_info = (struct ipa_dfs_info *) node->aux;


      v = node_dfs_info->next_cycle;
      while (v)
	{
	  push_node_to_stack (topo, v);
	  v = ((struct ipa_dfs_info *) v->aux)->next_cycle;
	}

      v = node;
      while (v)
	{
	  struct cgraph_edge *cs;

	  for (cs = v->callees; cs; cs = cs->next_callee)
	    if (edge_within_scc (cs)
		&& propagate_constants_accross_call (cs))
	      push_node_to_stack (topo, cs->callee);
	  v = pop_node_from_stack (topo);
	}


      v = node;
      while (v)
	{
	  struct cgraph_edge *cs;

	  estimate_local_effects (v);
	  add_all_node_vals_to_toposort (v);
	  for (cs = v->callees; cs; cs = cs->next_callee)
	    if (!edge_within_scc (cs))
	      propagate_constants_accross_call (cs);

	  v = ((struct ipa_dfs_info *) v->aux)->next_cycle;
	}
    }
}
