evolution_function_right_is_integer_cst (const_tree chrec)
{
  if (chrec == NULL_TREE)
    return false;

  switch (TREE_CODE (chrec))
    {
    case INTEGER_CST:
      return true;

    case POLYNOMIAL_CHREC:
      return TREE_CODE (CHREC_RIGHT (chrec)) == INTEGER_CST
	&& (TREE_CODE (CHREC_LEFT (chrec)) != POLYNOMIAL_CHREC
	    || evolution_function_right_is_integer_cst (CHREC_LEFT (chrec)));

    CASE_CONVERT:
      return evolution_function_right_is_integer_cst (TREE_OPERAND (chrec, 0));

    default:
      return false;
    }
}
