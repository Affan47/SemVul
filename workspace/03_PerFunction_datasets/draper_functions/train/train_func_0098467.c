c_tree_expr_nonnegative_p (tree t)
{
  if (TREE_CODE (t) == STMT_EXPR)
    {
      t = COMPOUND_BODY (STMT_EXPR_STMT (t));


      while (TREE_CHAIN (t) != NULL_TREE
             && TREE_CODE (TREE_CHAIN (t)) != SCOPE_STMT)
        t = TREE_CHAIN (t);
      return tree_expr_nonnegative_p (TREE_OPERAND (t, 0));
    }
  return tree_expr_nonnegative_p (t);
}
