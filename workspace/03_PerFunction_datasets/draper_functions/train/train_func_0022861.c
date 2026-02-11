nonbinary_modular_operation (enum tree_code op_code, tree type, tree lhs,
                             tree rhs)
{
  tree modulus = TYPE_MODULUS (type);
  unsigned int needed_precision = tree_floor_log2 (modulus) + 1;
  unsigned int precision;
  bool unsignedp = true;
  tree op_type = type;
  tree result;


  if (op_code == PLUS_EXPR && TREE_CODE (rhs) == INTEGER_CST)
    {
      rhs = fold_build2 (MINUS_EXPR, type, modulus, rhs);
      op_code = MINUS_EXPR;
    }


  if (op_code == PLUS_EXPR || op_code == MINUS_EXPR)
    needed_precision += 1;
  else if (op_code == MULT_EXPR)
    needed_precision *= 2;

  precision = MAX (needed_precision, TYPE_PRECISION (op_type));


  if (op_code == MINUS_EXPR)
    unsignedp = false;


  if (TYPE_PRECISION (op_type) < precision
      || TYPE_UNSIGNED (op_type) != unsignedp)
    {

      op_type = copy_node (gnat_type_for_size (precision, unsignedp));
      modulus = convert (op_type, modulus);
      SET_TYPE_MODULUS (op_type, modulus);
      TYPE_MODULAR_P (op_type) = 1;
      lhs = convert (op_type, lhs);
      rhs = convert (op_type, rhs);
    }


  result = fold_build2 (op_code, op_type, lhs, rhs);


  if (op_code == MULT_EXPR)
    {
      tree div_type = copy_node (gnat_type_for_size (needed_precision, 1));
      modulus = convert (div_type, modulus);
      SET_TYPE_MODULUS (div_type, modulus);
      TYPE_MODULAR_P (div_type) = 1;
      result = convert (op_type,
			fold_build2 (TRUNC_MOD_EXPR, div_type,
				     convert (div_type, result), modulus));
    }


  else if (op_code == MINUS_EXPR)
    {
      result = gnat_protect_expr (result);
      result = fold_build3 (COND_EXPR, op_type,
			    fold_build2 (LT_EXPR, boolean_type_node, result,
					 convert (op_type, integer_zero_node)),
			    fold_build2 (PLUS_EXPR, op_type, result, modulus),
			    result);
    }


  else
    {
      result = gnat_protect_expr (result);
      result = fold_build3 (COND_EXPR, op_type,
			    fold_build2 (GE_EXPR, boolean_type_node,
					 result, modulus),
			    fold_build2 (MINUS_EXPR, op_type,
					 result, modulus),
			    result);
    }

  return convert (type, result);
}
