avl_verify_rank (avl_node * node)
{
  if (!node) {
    return 0;
  } else {
    unsigned long num_left=0, num_right=0;
    if (node->left) {
      num_left = avl_verify_rank (node->left);
    }
    if (node->right) {
      num_right = avl_verify_rank (node->right);
    }
    if (AVL_GET_RANK (node) != num_left + 1) {
      fprintf (stderr, "invalid rank at node %ld\n", (long) node->key);
      exit (1);
    }
    return (num_left + num_right + 1);
  }
}
