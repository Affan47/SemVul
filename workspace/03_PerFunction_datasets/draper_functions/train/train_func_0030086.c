rbtree_node_alloc(rbtree_tree *tree,void *key,void *value)
{
   rbtree_node *node;

   if (!(node = mp_alloc_n0(&tree->mp,sizeof(*node))))
      return NULL;

   node->key = key;
   node->value = value;
   node->left = rbtree_nil(tree);
   node->right = rbtree_nil(tree);
   node->parent = rbtree_nil(tree);
   node->color = -1;
   return node;
}
