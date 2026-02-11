verify_cgraph (void)
{
  struct cgraph_node *node;

  if (seen_error ())
    return;

  FOR_EACH_FUNCTION (node)
    verify_cgraph_node (node);
}
