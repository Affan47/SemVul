expand_builtin_classify_type (tree exp)
{
  if (call_expr_nargs (exp))
    return GEN_INT (type_to_class (TREE_TYPE (CALL_EXPR_ARG (exp, 0))));
  return GEN_INT (no_type_class);
}
