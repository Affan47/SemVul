vect_recog_widen_shift_pattern (vec<gimple> *stmts,
				tree *type_in, tree *type_out)
{
  gimple last_stmt = stmts->pop ();
  gimple def_stmt0;
  tree oprnd0, oprnd1;
  tree type, half_type0;
  gimple pattern_stmt;
  tree vectype, vectype_out = NULL_TREE;
  tree var;
  enum tree_code dummy_code;
  int dummy_int;
  vec<tree>  dummy_vec;
  gimple use_stmt;
  bool promotion;

  if (!is_gimple_assign (last_stmt) || !vinfo_for_stmt (last_stmt))
    return NULL;

  if (STMT_VINFO_IN_PATTERN_P (vinfo_for_stmt (last_stmt)))
    return NULL;

  if (gimple_assign_rhs_code (last_stmt) != LSHIFT_EXPR)
    return NULL;

  oprnd0 = gimple_assign_rhs1 (last_stmt);
  oprnd1 = gimple_assign_rhs2 (last_stmt);
  if (TREE_CODE (oprnd0) != SSA_NAME || TREE_CODE (oprnd1) != INTEGER_CST)
    return NULL;


  if (!type_conversion_p (oprnd0, last_stmt, false, &half_type0, &def_stmt0,
                          &promotion)
      || !promotion)
     return NULL;


  if (tree_int_cst_compare (oprnd1, size_zero_node) <= 0)
    return NULL;

  oprnd0 = gimple_assign_rhs1 (def_stmt0);
  type = gimple_expr_type (last_stmt);


  use_stmt = vect_single_imm_use (last_stmt);
  if (use_stmt && is_gimple_assign (use_stmt)
      && CONVERT_EXPR_CODE_P (gimple_assign_rhs_code (use_stmt))
      && !STMT_VINFO_IN_PATTERN_P (vinfo_for_stmt (use_stmt)))
    {
      tree use_lhs = gimple_assign_lhs (use_stmt);
      tree use_type = TREE_TYPE (use_lhs);

      if (INTEGRAL_TYPE_P (use_type)
	  && TYPE_PRECISION (use_type) <= TYPE_PRECISION (type))
	{
	  last_stmt = use_stmt;
	  type = use_type;
	}
    }


  if (!vect_handle_widen_op_by_const (last_stmt, LSHIFT_EXPR, oprnd1,
       				      &oprnd0, stmts,
	                              type, &half_type0, def_stmt0))
    return NULL;


  if (dump_enabled_p ())
    dump_printf_loc (MSG_OPTIMIZED_LOCATIONS, vect_location,
                     "vect_recog_widen_shift_pattern: detected: ");


  vectype = get_vectype_for_scalar_type (half_type0);
  vectype_out = get_vectype_for_scalar_type (type);

  if (!vectype
      || !vectype_out
      || !supportable_widening_operation (WIDEN_LSHIFT_EXPR, last_stmt,
					  vectype_out, vectype,
					  &dummy_code, &dummy_code,
					  &dummy_int, &dummy_vec))
    return NULL;

  *type_in = vectype;
  *type_out = vectype_out;


  var = vect_recog_temp_ssa_var (type, NULL);
  pattern_stmt =
    gimple_build_assign_with_ops (WIDEN_LSHIFT_EXPR, var, oprnd0, oprnd1);

  if (dump_enabled_p ())
    dump_gimple_stmt_loc (MSG_NOTE, vect_location, TDF_SLIM, pattern_stmt, 0);

  stmts->safe_push (last_stmt);
  return pattern_stmt;
}
