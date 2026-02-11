simplify_conversion_using_ranges (gimple stmt)
{
  tree innerop, middleop, finaltype;
  gimple def_stmt;
  value_range_t *innervr;
  bool inner_unsigned_p, middle_unsigned_p, final_unsigned_p;
  unsigned inner_prec, middle_prec, final_prec;
  double_int innermin, innermed, innermax, middlemin, middlemed, middlemax;

  finaltype = TREE_TYPE (gimple_assign_lhs (stmt));
  if (!INTEGRAL_TYPE_P (finaltype))
    return false;
  middleop = gimple_assign_rhs1 (stmt);
  def_stmt = SSA_NAME_DEF_STMT (middleop);
  if (!is_gimple_assign (def_stmt)
      || !CONVERT_EXPR_CODE_P (gimple_assign_rhs_code (def_stmt)))
    return false;
  innerop = gimple_assign_rhs1 (def_stmt);
  if (TREE_CODE (innerop) != SSA_NAME)
    return false;


  innervr = get_value_range (innerop);
  if (innervr->type != VR_RANGE
      || TREE_CODE (innervr->min) != INTEGER_CST
      || TREE_CODE (innervr->max) != INTEGER_CST)
    return false;


  innermin = tree_to_double_int (innervr->min);
  innermax = tree_to_double_int (innervr->max);

  inner_prec = TYPE_PRECISION (TREE_TYPE (innerop));
  middle_prec = TYPE_PRECISION (TREE_TYPE (middleop));
  final_prec = TYPE_PRECISION (finaltype);


  if (double_int_cmp (double_int_sub (innermax, innermin),
		      double_int_mask (middle_prec), true) > 0
      && middle_prec < final_prec)
    return false;


  inner_unsigned_p = TYPE_UNSIGNED (TREE_TYPE (innerop));
  if (inner_unsigned_p)
    innermed = double_int_rshift (double_int_mask (inner_prec),
				  1, inner_prec, false);
  else
    innermed = double_int_zero;
  if (double_int_cmp (innermin, innermed, inner_unsigned_p) >= 0
      || double_int_cmp (innermed, innermax, inner_unsigned_p) >= 0)
    innermed = innermin;

  middle_unsigned_p = TYPE_UNSIGNED (TREE_TYPE (middleop));
  middlemin = double_int_ext (innermin, middle_prec, middle_unsigned_p);
  middlemed = double_int_ext (innermed, middle_prec, middle_unsigned_p);
  middlemax = double_int_ext (innermax, middle_prec, middle_unsigned_p);


  final_unsigned_p = TYPE_UNSIGNED (finaltype);
  if (!double_int_equal_p (double_int_ext (middlemin,
					   final_prec, final_unsigned_p),
			   double_int_ext (innermin,
					   final_prec, final_unsigned_p))
      || !double_int_equal_p (double_int_ext (middlemed,
					      final_prec, final_unsigned_p),
			      double_int_ext (innermed,
					      final_prec, final_unsigned_p))
      || !double_int_equal_p (double_int_ext (middlemax,
					      final_prec, final_unsigned_p),
			      double_int_ext (innermax,
					      final_prec, final_unsigned_p)))
    return false;

  gimple_assign_set_rhs1 (stmt, innerop);
  update_stmt (stmt);
  return true;
}
