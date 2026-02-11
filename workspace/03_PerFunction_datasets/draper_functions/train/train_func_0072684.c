tree_node_lookup (DirectNode *node,
                  void       *key)
{
     int cmp;

     if (!node)
          return NULL;

     cmp = key - node->key;
     if (cmp == 0)
          return node;

     if (cmp < 0 && node->left) {
          return tree_node_lookup (node->left, key);
     }
     else if (cmp > 0 && node->right) {
          return tree_node_lookup (node->right, key);
     }

     return NULL;
}
