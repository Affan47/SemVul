mem_expr_equal_p (tree expr1, tree expr2)
{
  if (expr1 == expr2)
    return 1;

  if (! expr1 || ! expr2)
    return 0;

  if (TREE_CODE (expr1) != TREE_CODE (expr2))
    return 0;

  if (TREE_CODE (expr1) == COMPONENT_REF)
    return
      mem_expr_equal_p (TREE_OPERAND (expr1, 0),
			TREE_OPERAND (expr2, 0))
      && mem_expr_equal_p (TREE_OPERAND (expr1, 1),
			   TREE_OPERAND (expr2, 1));

  if (TREE_CODE (expr1) == INDIRECT_REF)
    return mem_expr_equal_p (TREE_OPERAND (expr1, 0),
			     TREE_OPERAND (expr2, 0));


  if (DECL_P (expr1))
    return 0;

  abort();

}
