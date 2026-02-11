alloca_call_p (exp)
     tree exp;
{
  if (TREE_CODE (exp) == CALL_EXPR
      && TREE_CODE (TREE_OPERAND (exp, 0)) == ADDR_EXPR
      && (TREE_CODE (TREE_OPERAND (TREE_OPERAND (exp, 0), 0))
	  == FUNCTION_DECL)
      && (special_function_p (TREE_OPERAND (TREE_OPERAND (exp, 0), 0),
			      0) & ECF_MAY_BE_ALLOCA))
    return true;
  return false;
}
