copy_list (tree list)
{
  tree head;
  tree prev, next;

  if (list == 0)
    return 0;

  head = prev = copy_node (list);
  next = TREE_CHAIN (list);
  while (next)
    {
      TREE_CHAIN (prev) = copy_node (next);
      prev = TREE_CHAIN (prev);
      next = TREE_CHAIN (next);
    }
  return head;
}
