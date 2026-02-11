pointer_int_sum (resultcode, ptrop, intop)
     enum tree_code resultcode;
     tree ptrop, intop;
{
  tree size_exp;

  tree result;
  tree folded;


  tree result_type = TREE_TYPE (ptrop);

  if (TREE_CODE (TREE_TYPE (result_type)) == VOID_TYPE)
    {
      if (pedantic || warn_pointer_arith)
	pedwarn ("pointer of type `void *' used in arithmetic");
      size_exp = integer_one_node;
    }
  else if (TREE_CODE (TREE_TYPE (result_type)) == FUNCTION_TYPE)
    {
      if (pedantic || warn_pointer_arith)
	pedwarn ("pointer to a function used in arithmetic");
      size_exp = integer_one_node;
    }
  else if (TREE_CODE (TREE_TYPE (result_type)) == METHOD_TYPE)
    {
      if (pedantic || warn_pointer_arith)
	pedwarn ("pointer to member function used in arithmetic");
      size_exp = integer_one_node;
    }
  else if (TREE_CODE (TREE_TYPE (result_type)) == OFFSET_TYPE)
    {
      if (pedantic || warn_pointer_arith)
	pedwarn ("pointer to a member used in arithmetic");
      size_exp = integer_one_node;
    }
  else
    size_exp = size_in_bytes (TREE_TYPE (result_type));


  if ((TREE_CODE (intop) == PLUS_EXPR || TREE_CODE (intop) == MINUS_EXPR)
      && ! TREE_CONSTANT (intop)
      && TREE_CONSTANT (TREE_OPERAND (intop, 1))
      && TREE_CONSTANT (size_exp)


      && TREE_CODE (TREE_TYPE (TREE_OPERAND (intop, 0))) == INTEGER_TYPE


      && (! TREE_UNSIGNED (TREE_TYPE (intop))
	  || (TYPE_PRECISION (TREE_TYPE (intop))
	      == TYPE_PRECISION (TREE_TYPE (ptrop)))))
    {
      enum tree_code subcode = resultcode;
      tree int_type = TREE_TYPE (intop);
      if (TREE_CODE (intop) == MINUS_EXPR)
	subcode = (subcode == PLUS_EXPR ? MINUS_EXPR : PLUS_EXPR);


      ptrop = build_binary_op (subcode, ptrop,
			       convert (int_type, TREE_OPERAND (intop, 1)), 1);
      intop = convert (int_type, TREE_OPERAND (intop, 0));
    }


  if (TYPE_PRECISION (TREE_TYPE (intop)) != TYPE_PRECISION (sizetype)
      || TREE_UNSIGNED (TREE_TYPE (intop)) != TREE_UNSIGNED (sizetype))
    intop = convert (c_common_type_for_size (TYPE_PRECISION (sizetype),
					     TREE_UNSIGNED (sizetype)), intop);


  intop = convert (result_type,
		   build_binary_op (MULT_EXPR, intop,
				    convert (TREE_TYPE (intop), size_exp), 1));


  result = build (resultcode, result_type, ptrop, intop);

  folded = fold (result);
  if (folded == result)
    TREE_CONSTANT (folded) = TREE_CONSTANT (ptrop) & TREE_CONSTANT (intop);
  return folded;
}
