free_tree(root)
   TREE *root;
{
   if (root == NULL) return;

   free_tree(NEXT(root));
   free_tree(LINK(root));
   free_tree(LEFT(root));
   free_tree(RIGHT(root));
   free_treeentry(&root->tentry);
   FREEMEM((char *)root);
}
