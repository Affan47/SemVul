markup_tree_unref (MarkupTree *tree)
{
  g_return_if_fail (tree != NULL);
  g_return_if_fail (tree->refcount > 0);

  if (tree->refcount > 1)
    {
      tree->refcount -= 1;
      return;
    }

  g_hash_table_remove (trees_by_root_dir, tree->dirname);
  if (g_hash_table_size (trees_by_root_dir) == 0)
    {
      g_hash_table_destroy (trees_by_root_dir);
      trees_by_root_dir = NULL;
    }

  markup_dir_free (tree->root);
  tree->root = NULL;

  g_free (tree->dirname);

  g_free (tree);
}
