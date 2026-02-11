fold_builtin_frexp (location_t loc, tree arg0, tree arg1, tree rettype)
{
  if (! validate_arg (arg0, REAL_TYPE) || ! validate_arg (arg1, POINTER_TYPE))
    return NULL_TREE;

  STRIP_NOPS (arg0);

  if (!(TREE_CODE (arg0) == REAL_CST && ! TREE_OVERFLOW (arg0)))
    return NULL_TREE;

  arg1 = build_fold_indirect_ref_loc (loc, arg1);


  if (TYPE_MAIN_VARIANT (TREE_TYPE (arg1)) == integer_type_node)
    {
      const REAL_VALUE_TYPE *const value = TREE_REAL_CST_PTR (arg0);
      tree frac, exp;

      switch (value->cl)
      {
      case rvc_zero:

	exp = integer_zero_node;
	frac = arg0;
	break;
      case rvc_nan:
      case rvc_inf:

	return omit_one_operand_loc (loc, rettype, arg0, arg1);
      case rvc_normal:
	{


	  REAL_VALUE_TYPE frac_rvt = *value;
	  SET_REAL_EXP (&frac_rvt, 0);
	  frac = build_real (rettype, frac_rvt);
	  exp = build_int_cst (integer_type_node, REAL_EXP (value));
	}
	break;
      default:
	gcc_unreachable ();
      }


      arg1 = fold_build2_loc (loc, MODIFY_EXPR, rettype, arg1, exp);
      TREE_SIDE_EFFECTS (arg1) = 1;
      return fold_build2_loc (loc, COMPOUND_EXPR, rettype, arg1, frac);
    }

  return NULL_TREE;
}
