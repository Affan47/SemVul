put_pending_size (tree expr)
{


  expr = skip_simple_arithmetic (expr);

  if (TREE_CODE (expr) == SAVE_EXPR)
    pending_sizes = tree_cons (NULL_TREE, expr, pending_sizes);
}
