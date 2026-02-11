free_subtree(bc_node *n)
{
   int i;

   if (n == NULL) return;

   for (i = n->bobj.child_num - 1; i >= 0; i--)
      free_subtree(n->children[i]);
   free_tree_node(n);
}
