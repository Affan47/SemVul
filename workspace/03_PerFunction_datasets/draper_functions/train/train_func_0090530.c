cgraph_node_remove_callers (struct cgraph_node *node)
{
  struct cgraph_edge *e, *f;


  for (e = node->callers; e; e = f)
    {
      f = e->next_caller;
      cgraph_call_edge_removal_hooks (e);
      cgraph_edge_remove_caller (e);
      cgraph_free_edge (e);
    }
  node->callers = NULL;
}
