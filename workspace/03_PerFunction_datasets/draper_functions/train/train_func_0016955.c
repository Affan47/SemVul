avl_tree_new (avl_key_compare_fun_type compare_fun,
          void * compare_arg)
{
  avl_tree * t = (avl_tree *) malloc (sizeof (avl_tree));

  if (!t) {
    return NULL;
  } else {
    avl_node * root = avl_node_new((void *)NULL, (avl_node *) NULL);
    if (!root) {
      free (t);
      return NULL;
    } else {
      t->root = root;
      t->height = 0;
      t->length = 0;
      t->compare_fun = compare_fun;
      t->compare_arg = compare_arg;
      thread_rwlock_create(&t->rwlock);
      return t;
    }
  }
}
