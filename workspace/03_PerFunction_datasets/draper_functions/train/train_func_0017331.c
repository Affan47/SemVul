glp_ios_pool_size(glp_tree *tree)
{
      if (tree->reason != GLP_ICUTGEN)
         xerror("glp_ios_pool_size: operation not allowed\n");
      xassert(tree->local != NULL);
      return tree->local->size;
}
