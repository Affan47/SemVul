stabilize_expr (tree exp, tree* initp)
{
  tree init_expr;

  if (!TREE_SIDE_EFFECTS (exp))
    {
      init_expr = NULL_TREE;
    }
  else if (!real_lvalue_p (exp)
	   || !TYPE_NEEDS_CONSTRUCTING (TREE_TYPE (exp)))
    {
      init_expr = get_target_expr (exp);
      exp = TARGET_EXPR_SLOT (init_expr);
    }
  else
    {
      exp = build_unary_op (ADDR_EXPR, exp, 1);
      init_expr = get_target_expr (exp);
      exp = TARGET_EXPR_SLOT (init_expr);
      exp = build_indirect_ref (exp, 0);
    }

  *initp = init_expr;
  return exp;
}
