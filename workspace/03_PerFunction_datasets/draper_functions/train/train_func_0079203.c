check_omp_for_incr_expr (location_t loc, tree exp, tree decl)
{
  tree t;

  if (!INTEGRAL_TYPE_P (TREE_TYPE (exp))
      || TYPE_PRECISION (TREE_TYPE (exp)) < TYPE_PRECISION (TREE_TYPE (decl)))
    return error_mark_node;

  if (exp == decl)
    return build_int_cst (TREE_TYPE (exp), 0);

  switch (TREE_CODE (exp))
    {
    CASE_CONVERT:
      t = check_omp_for_incr_expr (loc, TREE_OPERAND (exp, 0), decl);
      if (t != error_mark_node)
        return fold_convert_loc (loc, TREE_TYPE (exp), t);
      break;
    case MINUS_EXPR:
      t = check_omp_for_incr_expr (loc, TREE_OPERAND (exp, 0), decl);
      if (t != error_mark_node)
        return fold_build2_loc (loc, MINUS_EXPR,
			    TREE_TYPE (exp), t, TREE_OPERAND (exp, 1));
      break;
    case PLUS_EXPR:
      t = check_omp_for_incr_expr (loc, TREE_OPERAND (exp, 0), decl);
      if (t != error_mark_node)
        return fold_build2_loc (loc, PLUS_EXPR,
			    TREE_TYPE (exp), t, TREE_OPERAND (exp, 1));
      t = check_omp_for_incr_expr (loc, TREE_OPERAND (exp, 1), decl);
      if (t != error_mark_node)
        return fold_build2_loc (loc, PLUS_EXPR,
			    TREE_TYPE (exp), TREE_OPERAND (exp, 0), t);
      break;
    default:
      break;
    }

  return error_mark_node;
}
