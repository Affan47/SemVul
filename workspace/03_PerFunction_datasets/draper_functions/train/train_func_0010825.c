interval_tree_search_internal(GtIntervalTree *it,
                                                         GtIntervalTreeNode
                                                          *node,
                                                         unsigned long low,
                                                         unsigned long high)
{
  GtIntervalTreeNode *x;
  x = node;

  while (x != it->nil && !(low <= x->high && x->low <= high)) {
    if (x->left != it->nil && x->left->max >= low)
      x = x->left;
    else
      x = x->right;
  }
  return (x == it->nil) ? NULL : x;
}
