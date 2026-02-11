cgraph_assemble_pending_functions (void)
{
  bool output = false;

  if (flag_unit_at_a_time)
    return false;

  while (cgraph_nodes_queue)
    {
      struct cgraph_node *n = cgraph_nodes_queue;

      cgraph_nodes_queue = cgraph_nodes_queue->next_needed;
      if (!n->origin && !DECL_EXTERNAL (n->decl))
	{
	  cgraph_expand_function (n);
	  output = true;
	}
    }

  return output;
}
