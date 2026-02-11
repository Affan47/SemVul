check_caller_edge (struct cgraph_node *node, void *edge)
{
  return (node->callers
          && node->callers != edge);
}
