inline_conversion (tree exp)
{
  if (TREE_CODE (exp) == FUNCTION_DECL)
    exp = build1 (ADDR_EXPR, build_pointer_type (TREE_TYPE (exp)), exp);

  return exp;
}
