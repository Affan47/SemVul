get_call_expr_in (tree t)
{
  if (TREE_CODE (t) == MODIFY_EXPR)
    t = TREE_OPERAND (t, 1);
  if (TREE_CODE (t) == WITH_SIZE_EXPR)
    t = TREE_OPERAND (t, 0);
  if (TREE_CODE (t) == CALL_EXPR)
    return t;
  return NULL_TREE;
}
