vect_recog_vector_vector_shift_pattern (vec<gimple> *stmts,
					tree *type_in, tree *type_out)
{
  gimple last_stmt = stmts->pop ();
  tree oprnd0, oprnd1, lhs, var;
  gimple pattern_stmt, def_stmt;
  enum tree_code rhs_code;
  stmt_vec_info stmt_vinfo = vinfo_for_stmt (last_stmt);
  loop_vec_info loop_vinfo = STMT_VINFO_LOOP_VINFO (stmt_vinfo);
  bb_vec_info bb_vinfo = STMT_VINFO_BB_VINFO (stmt_vinfo);
  enum vect_def_type dt;
  tree def;

  if (!is_gimple_assign (last_stmt))
    return NULL;

  rhs_code = gimple_assign_rhs_code (last_stmt);
  switch (rhs_code)
    {
    case LSHIFT_EXPR:
    case RSHIFT_EXPR:
    case LROTATE_EXPR:
    case RROTATE_EXPR:
      break;
    default:
      return NULL;
    }

  if (STMT_VINFO_IN_PATTERN_P (stmt_vinfo))
    return NULL;

  lhs = gimple_assign_lhs (last_stmt);
  oprnd0 = gimple_assign_rhs1 (last_stmt);
  oprnd1 = gimple_assign_rhs2 (last_stmt);
  if (TREE_CODE (oprnd0) != SSA_NAME
      || TREE_CODE (oprnd1) != SSA_NAME
      || TYPE_MODE (TREE_TYPE (oprnd0)) == TYPE_MODE (TREE_TYPE (oprnd1))
      || TYPE_PRECISION (TREE_TYPE (oprnd1))
	 != GET_MODE_PRECISION (TYPE_MODE (TREE_TYPE (oprnd1)))
      || TYPE_PRECISION (TREE_TYPE (lhs))
	 != TYPE_PRECISION (TREE_TYPE (oprnd0)))
    return NULL;

  if (!vect_is_simple_use (oprnd1, last_stmt, loop_vinfo, bb_vinfo, &def_stmt,
			   &def, &dt))
    return NULL;

  if (dt != vect_internal_def)
    return NULL;

  *type_in = get_vectype_for_scalar_type (TREE_TYPE (oprnd0));
  *type_out = *type_in;
  if (*type_in == NULL_TREE)
    return NULL;

  def = NULL_TREE;
  if (gimple_assign_cast_p (def_stmt))
    {
      tree rhs1 = gimple_assign_rhs1 (def_stmt);
      if (TYPE_MODE (TREE_TYPE (rhs1)) == TYPE_MODE (TREE_TYPE (oprnd0))
	  && TYPE_PRECISION (TREE_TYPE (rhs1))
	     == TYPE_PRECISION (TREE_TYPE (oprnd0)))
	def = rhs1;
    }

  if (def == NULL_TREE)
    {
      def = vect_recog_temp_ssa_var (TREE_TYPE (oprnd0), NULL);
      def_stmt = gimple_build_assign_with_ops (NOP_EXPR, def, oprnd1,
					       NULL_TREE);
      new_pattern_def_seq (stmt_vinfo, def_stmt);
    }


  if (dump_enabled_p ())
    dump_printf_loc (MSG_OPTIMIZED_LOCATIONS, vect_location,
                     "vect_recog_vector_vector_shift_pattern: detected: ");


  var = vect_recog_temp_ssa_var (TREE_TYPE (oprnd0), NULL);
  pattern_stmt = gimple_build_assign_with_ops (rhs_code, var, oprnd0, def);

  if (dump_enabled_p ())
    dump_gimple_stmt_loc (MSG_NOTE, vect_location, TDF_SLIM, pattern_stmt, 0);

  stmts->safe_push (last_stmt);
  return pattern_stmt;
}
