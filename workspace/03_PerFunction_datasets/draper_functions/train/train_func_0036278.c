interval_tree_find_all_internal(GtIntervalTree *it,
                                            GtIntervalTreeNode *node,
                                            GtIntervalTreeIteratorFunc func,
                                            unsigned long low,
                                            unsigned long high,
                                            void *data)
{
  GtIntervalTreeNode* x;
  if (node == it->nil) return;
  x = node;
  if (low <= x->high && x->low <= high)
    func(node, data);

  if (x->left != it->nil && low <= x->left->max)
    interval_tree_find_all_internal(it, x->left, func, low, high, data);
  if (x->right != it->nil && low <= x->right->max)
    interval_tree_find_all_internal(it, x->right, func, low, high, data);
}
