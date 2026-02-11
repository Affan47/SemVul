vect_is_simple_use (tree operand, gimple stmt, loop_vec_info loop_vinfo,
                    bb_vec_info bb_vinfo, gimple *def_stmt,
		    tree *def, enum vect_def_type *dt)
{
  basic_block bb;
  stmt_vec_info stmt_vinfo;
  struct loop *loop = NULL;

  if (loop_vinfo)
    loop = LOOP_VINFO_LOOP (loop_vinfo);

  *def_stmt = NULL;
  *def = NULL_TREE;

  if (dump_enabled_p ())
    {
      dump_printf_loc (MSG_NOTE, vect_location,
                       "vect_is_simple_use: operand ");
      dump_generic_expr (MSG_NOTE, TDF_SLIM, operand);
    }

  if (CONSTANT_CLASS_P (operand))
    {
      *dt = vect_constant_def;
      return true;
    }

  if (is_gimple_min_invariant (operand))
    {
      *def = operand;
      *dt = vect_external_def;
      return true;
    }

  if (TREE_CODE (operand) == PAREN_EXPR)
    {
      if (dump_enabled_p ())
        dump_printf_loc (MSG_NOTE, vect_location, "non-associatable copy.");
      operand = TREE_OPERAND (operand, 0);
    }

  if (TREE_CODE (operand) != SSA_NAME)
    {
      if (dump_enabled_p ())
        dump_printf_loc (MSG_MISSED_OPTIMIZATION, vect_location,
                         "not ssa-name.");
      return false;
    }

  *def_stmt = SSA_NAME_DEF_STMT (operand);
  if (*def_stmt == NULL)
    {
      if (dump_enabled_p ())
        dump_printf_loc (MSG_MISSED_OPTIMIZATION, vect_location,
                         "no def_stmt.");
      return false;
    }

  if (dump_enabled_p ())
    {
      dump_printf_loc (MSG_NOTE, vect_location, "def_stmt: ");
      dump_gimple_stmt (MSG_NOTE, TDF_SLIM, *def_stmt, 0);
    }


  if (gimple_nop_p (*def_stmt))
    {
      *def = operand;
      *dt = vect_external_def;
      return true;
    }

  bb = gimple_bb (*def_stmt);

  if ((loop && !flow_bb_inside_loop_p (loop, bb))
      || (!loop && bb != BB_VINFO_BB (bb_vinfo))
      || (!loop && gimple_code (*def_stmt) == GIMPLE_PHI))
    *dt = vect_external_def;
  else
    {
      stmt_vinfo = vinfo_for_stmt (*def_stmt);
      *dt = STMT_VINFO_DEF_TYPE (stmt_vinfo);
    }

  if (*dt == vect_unknown_def_type
      || (stmt
	  && *dt == vect_double_reduction_def
	  && gimple_code (stmt) != GIMPLE_PHI))
    {
      if (dump_enabled_p ())
        dump_printf_loc (MSG_MISSED_OPTIMIZATION, vect_location,
                         "Unsupported pattern.");
      return false;
    }

  if (dump_enabled_p ())
    dump_printf_loc (MSG_NOTE, vect_location, "type of def: %d.", *dt);

  switch (gimple_code (*def_stmt))
    {
    case GIMPLE_PHI:
      *def = gimple_phi_result (*def_stmt);
      break;

    case GIMPLE_ASSIGN:
      *def = gimple_assign_lhs (*def_stmt);
      break;

    case GIMPLE_CALL:
      *def = gimple_call_lhs (*def_stmt);
      if (*def != NULL)
	break;

    default:
      if (dump_enabled_p ())
        dump_printf_loc (MSG_MISSED_OPTIMIZATION, vect_location,
                         "unsupported defining stmt: ");
      return false;
    }

  return true;
}
