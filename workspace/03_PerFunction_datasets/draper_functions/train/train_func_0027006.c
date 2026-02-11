widening_mult_conversion_strippable_p (tree result_type, gimple stmt)
{
  enum tree_code rhs_code = gimple_assign_rhs_code (stmt);

  if (TREE_CODE (result_type) == INTEGER_TYPE)
    {
      tree op_type;
      tree inner_op_type;

      if (!CONVERT_EXPR_CODE_P (rhs_code))
	return false;

      op_type = TREE_TYPE (gimple_assign_lhs (stmt));


      if (TYPE_PRECISION (result_type) == TYPE_PRECISION (op_type))
	return true;


      inner_op_type = TREE_TYPE (gimple_assign_rhs1 (stmt));


      if ((TYPE_UNSIGNED (inner_op_type)
	   || TYPE_UNSIGNED (op_type) == TYPE_UNSIGNED (inner_op_type))
	  && TYPE_PRECISION (op_type) > TYPE_PRECISION (inner_op_type))
	return true;

      return false;
    }

  return rhs_code == FIXED_CONVERT_EXPR;
}
