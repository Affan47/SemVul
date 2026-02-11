get_constant(tree expr, unsigned HOST_WIDE_INT *value, int validated_p)
{
  while (TREE_CODE (expr) == NOP_EXPR
	 || TREE_CODE (expr) == CONVERT_EXPR
	 || TREE_CODE (expr) == NON_LVALUE_EXPR)
    expr = TREE_OPERAND (expr, 0);

  if (TREE_CODE (expr) != INTEGER_CST || TREE_INT_CST_HIGH (expr) != 0)
    {
      if (validated_p)
	abort ();
      return false;
    }

  *value = TREE_INT_CST_LOW (expr);

  return true;
}
