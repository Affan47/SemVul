simplify_float_conversion_using_ranges (gimple_stmt_iterator *gsi, gimple stmt)
{
  tree rhs1 = gimple_assign_rhs1 (stmt);
  value_range_t *vr = get_value_range (rhs1);
  enum machine_mode fltmode = TYPE_MODE (TREE_TYPE (gimple_assign_lhs (stmt)));
  enum machine_mode mode;
  tree tem;
  gimple conv;


  if (vr->type != VR_RANGE
      || TREE_CODE (vr->min) != INTEGER_CST
      || TREE_CODE (vr->max) != INTEGER_CST)
    return false;


  if (TYPE_UNSIGNED (TREE_TYPE (rhs1))
      && (can_float_p (fltmode, TYPE_MODE (TREE_TYPE (rhs1)), 0)
	  != CODE_FOR_nothing)
      && range_fits_type_p (vr, GET_MODE_PRECISION
			          (TYPE_MODE (TREE_TYPE (rhs1))), 0))
    mode = TYPE_MODE (TREE_TYPE (rhs1));

  else if (can_float_p (fltmode, TYPE_MODE (TREE_TYPE (rhs1)),
			TYPE_UNSIGNED (TREE_TYPE (rhs1))))
    return false;


  else
    {
      mode = GET_CLASS_NARROWEST_MODE (MODE_INT);
      do
	{


	  if (can_float_p (fltmode, mode, 0) != CODE_FOR_nothing
	      && range_fits_type_p (vr, GET_MODE_PRECISION (mode), 0))
	    break;

	  mode = GET_MODE_WIDER_MODE (mode);


	  if (GET_MODE_PRECISION (mode) > TYPE_PRECISION (TREE_TYPE (rhs1)))
	    return false;
	}
      while (mode != VOIDmode);
      if (mode == VOIDmode)
	return false;
    }


  tem = create_tmp_var (build_nonstandard_integer_type
			  (GET_MODE_PRECISION (mode), 0), NULL);
  conv = gimple_build_assign_with_ops (NOP_EXPR, tem, rhs1, NULL_TREE);
  tem = make_ssa_name (tem, conv);
  gimple_assign_set_lhs (conv, tem);
  gsi_insert_before (gsi, conv, GSI_SAME_STMT);
  gimple_assign_set_rhs1 (stmt, tem);
  update_stmt (stmt);

  return true;
}
