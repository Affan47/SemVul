cgraph_remove_node_and_inline_clones (struct cgraph_node *node, struct cgraph_node *forbidden_node)
{
  struct cgraph_edge *e, *next;
  bool found = false;

  if (node == forbidden_node)
    return true;
  for (e = node->callees; e; e = next)
    {
      next = e->next_callee;
      if (!e->inline_failed)
        found |= cgraph_remove_node_and_inline_clones (e->callee, forbidden_node);
    }
  cgraph_remove_node (node);
  return found;
}
