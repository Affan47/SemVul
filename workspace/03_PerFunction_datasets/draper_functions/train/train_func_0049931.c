constant_multiple_of (tree top, tree bot, double_int *mul)
{
  tree mby;
  enum tree_code code;
  double_int res, p0, p1;
  unsigned precision = TYPE_PRECISION (TREE_TYPE (top));

  STRIP_NOPS (top);
  STRIP_NOPS (bot);

  if (operand_equal_p (top, bot, 0))
    {
      *mul = double_int_one;
      return true;
    }

  code = TREE_CODE (top);
  switch (code)
    {
    case MULT_EXPR:
      mby = TREE_OPERAND (top, 1);
      if (TREE_CODE (mby) != INTEGER_CST)
	return false;

      if (!constant_multiple_of (TREE_OPERAND (top, 0), bot, &res))
	return false;

      *mul = (res * tree_to_double_int (mby)).sext (precision);
      return true;

    case PLUS_EXPR:
    case MINUS_EXPR:
      if (!constant_multiple_of (TREE_OPERAND (top, 0), bot, &p0)
	  || !constant_multiple_of (TREE_OPERAND (top, 1), bot, &p1))
	return false;

      if (code == MINUS_EXPR)
	p1 = -p1;
      *mul = (p0 + p1).sext (precision);
      return true;

    case INTEGER_CST:
      if (TREE_CODE (bot) != INTEGER_CST)
	return false;

      p0 = tree_to_double_int (top).sext (precision);
      p1 = tree_to_double_int (bot).sext (precision);
      if (p1.is_zero ())
	return false;
      *mul = p0.sdivmod (p1, FLOOR_DIV_EXPR, &res).sext (precision);
      return res.is_zero ();

    default:
      return false;
    }
}
