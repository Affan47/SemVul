is_overloaded_fn (tree x)
{

  if (TREE_CODE (x) == OFFSET_REF
      || TREE_CODE (x) == COMPONENT_REF)
    x = TREE_OPERAND (x, 1);
  if (BASELINK_P (x))
    x = BASELINK_FUNCTIONS (x);
  if (TREE_CODE (x) == TEMPLATE_ID_EXPR)
    x = TREE_OPERAND (x, 0);
  if (DECL_FUNCTION_TEMPLATE_P (OVL_CURRENT (x))
      || (TREE_CODE (x) == OVERLOAD && OVL_CHAIN (x)))
    return 2;
  return  (TREE_CODE (x) == FUNCTION_DECL
	   || TREE_CODE (x) == OVERLOAD);
}
