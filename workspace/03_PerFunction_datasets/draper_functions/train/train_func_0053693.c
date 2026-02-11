d_build_truthvalue_op (tree_code code, tree orig_op0,
		       tree orig_op1, int convert_p)
{
  tree type0, type1;
  tree op0, op1;

  tree result_type = NULL_TREE;

  if (convert_p)
    {
      op0 = d_scalar_conversion (orig_op0);
      op1 = d_scalar_conversion (orig_op1);
    }
  else
    {
      op0 = orig_op0;
      op1 = orig_op1;
    }

  type0 = TREE_TYPE (op0);
  type1 = TREE_TYPE (op1);


  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);


  if (POINTER_TYPE_P (type0) && TREE_CODE (op1) == INTEGER_CST
      && integer_zerop (op1))
    {
      result_type = type0;
    }
  else if (POINTER_TYPE_P (type1) && TREE_CODE (op0) == INTEGER_CST
	   && integer_zerop (op0))
    {
      result_type = type1;
    }


  else if (INTEGRAL_TYPE_P (type0) && INTEGRAL_TYPE_P (type1))
    {
      if (TYPE_PRECISION (type0) > TYPE_PRECISION (type1))
	result_type = type0;
      else if (TYPE_PRECISION (type0) < TYPE_PRECISION (type1))
	result_type = type1;
      else if (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	result_type = TYPE_UNSIGNED (type0) ? type0 : type1;
    }

  if (result_type)
    {
      if (TREE_TYPE (op0) != result_type)
	op0 = d_convert_basic (result_type, op0);
      if (TREE_TYPE (op1) != result_type)
	op1 = d_convert_basic (result_type, op1);
    }

  return build2 (code, boolean_type_node, op0, op1);
}
