gt_rbtree_next_equal_key(GtRBTree *tree, void *key,
                               GtCompareWithData cmpfun, void *cmpinfo)
{
  int cmp;
  const GtRBTreeNode *current,
                     *found = NULL;
  gt_assert(tree);
  gt_assert(key);
  gt_assert(cmpfun);
  current = tree->root;

  while (current != NULL) {
    cmp = cmpfun(key, current->key, cmpinfo);
    if (cmp == 0) {
      return current->key;
    } else {
      if (cmp < 0) {
        found = current;
        current = current->link[0];
      } else {
        current = current->link[1];
      }
    }
  }
  if (found == NULL) {
    return NULL;
  }
  return found->key;
}
