avl_iterate_index_range (avl_tree * tree,
             avl_iter_index_fun_type iter_fun,
             unsigned long low,
             unsigned long high,
             void * iter_arg)
{
  unsigned long m;
  unsigned long num_left;
  avl_node * node;

  if (high > tree->length) {
    return -1;
  }
  num_left = (high - low);

  m = high;
  node = tree->root->right;
  while (1) {
    if (m < AVL_GET_RANK (node)) {
      node = node->left;
    } else if (m > AVL_GET_RANK (node)) {
      m = m - AVL_GET_RANK (node);
      node = node->right;
    } else {
      break;
    }
  }

  while (num_left) {
    num_left = num_left - 1;
    if (iter_fun (num_left, node->key, iter_arg) != 0) {
      return -1;
    }
    node = avl_get_prev (node);
  }
  return 0;
}
