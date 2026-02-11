update_all_callee_keys (fibheap_t heap, struct cgraph_node *node,
			bitmap updated_nodes)
{
  struct cgraph_edge *e = node->callees;
  node->global.estimated_growth = INT_MIN;

  if (!e)
    return;
  while (true)
    if (!e->inline_failed && e->callee->callees)
      e = e->callee->callees;
    else
      {
	if (e->inline_failed)
	  update_caller_keys (heap, e->callee, updated_nodes);
	if (e->next_callee)
	  e = e->next_callee;
	else
	  {
	    do
	      {
		if (e->caller == node)
		  return;
		e = e->caller->callers;
	      }
	    while (!e->next_callee);
	    e = e->next_callee;
	  }
      }
}
