fast_set_node (struct bintree *root, struct node *node, short depth)
{
  struct bintree *child;


  child = (struct bintree *) &tree_pool[tpp++];
  if (tpp >= MAXNODECHECK) {
    printf ("TPP=%d\n", tpp);
    fatal_error ("Out of memory, while building tree!");
  }
  child->parent = root;
  child->lson = NULL;
  child->rson = NULL;
  child->node = node;

  return child;
}
