update_caller_keys (fibheap_t heap, struct cgraph_node *node,
		    bitmap updated_nodes)
{
  struct cgraph_edge *edge;
  cgraph_inline_failed_t failed_reason;

  if (!node->local.inlinable
      || cgraph_function_body_availability (node) <= AVAIL_OVERWRITABLE
      || node->global.inlined_to)
    return;
  if (!bitmap_set_bit (updated_nodes, node->uid))
    return;
  node->global.estimated_growth = INT_MIN;


  for (edge = node->callers; edge; edge = edge->next_caller)
    if (edge->inline_failed)
      break;
  if (!edge)
    return;

  if (!cgraph_default_inline_p (node, &failed_reason))
    {
      for (; edge; edge = edge->next_caller)
	if (edge->aux)
	  {
	    fibheap_delete_node (heap, (fibnode_t) edge->aux);
	    edge->aux = NULL;
	    if (edge->inline_failed)
	      edge->inline_failed = failed_reason;
	  }
      return;
    }

  for (; edge; edge = edge->next_caller)
    if (edge->inline_failed)
      update_edge_key (heap, edge);
}
