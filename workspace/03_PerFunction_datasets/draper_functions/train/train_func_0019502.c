expr_size (exp)
     tree exp;
{
  tree size = (*lang_hooks.expr_size) (exp);

  if (TREE_CODE (size) != INTEGER_CST
      && contains_placeholder_p (size))
    size = build (WITH_RECORD_EXPR, sizetype, size, exp);

  return expand_expr (size, NULL_RTX, TYPE_MODE (sizetype), 0);
}
