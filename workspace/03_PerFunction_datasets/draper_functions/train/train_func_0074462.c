avl_node_new (void *        key,
          avl_node *    parent)
{
  avl_node * node = (avl_node *) malloc (sizeof (avl_node));

  if (!node) {
    return NULL;
  } else {
    node->parent = parent;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->rank_and_balance = 0;
    AVL_SET_BALANCE (node, 0);
    AVL_SET_RANK (node, 1);
#ifdef HAVE_AVL_NODE_LOCK
    thread_rwlock_create(&node->rwlock);
#endif
    return node;
  }
}
