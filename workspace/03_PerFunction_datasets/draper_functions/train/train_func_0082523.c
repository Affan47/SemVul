glp_ios_del_row(glp_tree *tree, int i)
{
      if (tree->reason != GLP_ICUTGEN)
         xerror("glp_ios_del_row: operation not allowed\n");
      ios_del_row(tree, tree->local, i);
      return;
}
