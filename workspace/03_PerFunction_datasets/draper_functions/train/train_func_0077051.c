gimplify_compound_expr (tree *expr_p, gimple_seq *pre_p, bool want_value)
{
  tree t = *expr_p;

  do
    {
      tree *sub_p = &TREE_OPERAND (t, 0);

      if (TREE_CODE (*sub_p) == COMPOUND_EXPR)
	gimplify_compound_expr (sub_p, pre_p, false);
      else
	gimplify_stmt (sub_p, pre_p);

      t = TREE_OPERAND (t, 1);
    }
  while (TREE_CODE (t) == COMPOUND_EXPR);

  *expr_p = t;
  if (want_value)
    return GS_OK;
  else
    {
      gimplify_stmt (expr_p, pre_p);
      return GS_ALL_DONE;
    }
}
