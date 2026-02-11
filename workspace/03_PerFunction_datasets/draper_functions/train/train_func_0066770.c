fold_builtin_cbrt (location_t loc, tree arg, tree type)
{
  const enum built_in_function fcode = builtin_mathfn_code (arg);
  tree res;

  if (!validate_arg (arg, REAL_TYPE))
    return NULL_TREE;


  if ((res = do_mpfr_arg1 (arg, type, mpfr_cbrt, NULL, NULL, 0)))
    return res;

  if (flag_unsafe_math_optimizations)
    {

      if (BUILTIN_EXPONENT_P (fcode))
	{
	  tree expfn = TREE_OPERAND (CALL_EXPR_FN (arg), 0);
	  const REAL_VALUE_TYPE third_trunc =
	    real_value_truncate (TYPE_MODE (type), dconst_third ());
	  arg = fold_build2_loc (loc, MULT_EXPR, type,
			     CALL_EXPR_ARG (arg, 0),
			     build_real (type, third_trunc));
	  return build_call_expr_loc (loc, expfn, 1, arg);
	}


      if (BUILTIN_SQRT_P (fcode))
	{
	  tree powfn = mathfn_built_in (type, BUILT_IN_POW);

	  if (powfn)
	    {
	      tree arg0 = CALL_EXPR_ARG (arg, 0);
	      tree tree_root;
	      REAL_VALUE_TYPE dconstroot = dconst_third ();

	      SET_REAL_EXP (&dconstroot, REAL_EXP (&dconstroot) - 1);
	      dconstroot = real_value_truncate (TYPE_MODE (type), dconstroot);
	      tree_root = build_real (type, dconstroot);
	      return build_call_expr_loc (loc, powfn, 2, arg0, tree_root);
	    }
	}


      if (BUILTIN_CBRT_P (fcode))
	{
	  tree arg0 = CALL_EXPR_ARG (arg, 0);
	  if (tree_expr_nonnegative_p (arg0))
	    {
	      tree powfn = mathfn_built_in (type, BUILT_IN_POW);

	      if (powfn)
		{
		  tree tree_root;
		  REAL_VALUE_TYPE dconstroot;

		  real_arithmetic (&dconstroot, MULT_EXPR,
                                   dconst_third_ptr (), dconst_third_ptr ());
		  dconstroot = real_value_truncate (TYPE_MODE (type), dconstroot);
		  tree_root = build_real (type, dconstroot);
		  return build_call_expr_loc (loc, powfn, 2, arg0, tree_root);
		}
	    }
	}


      if (fcode == BUILT_IN_POW
          || fcode == BUILT_IN_POWF
	  || fcode == BUILT_IN_POWL)
	{
	  tree arg00 = CALL_EXPR_ARG (arg, 0);
	  tree arg01 = CALL_EXPR_ARG (arg, 1);
	  if (tree_expr_nonnegative_p (arg00))
	    {
	      tree powfn = TREE_OPERAND (CALL_EXPR_FN (arg), 0);
	      const REAL_VALUE_TYPE dconstroot
		= real_value_truncate (TYPE_MODE (type), dconst_third ());
	      tree narg01 = fold_build2_loc (loc, MULT_EXPR, type, arg01,
					 build_real (type, dconstroot));
	      return build_call_expr_loc (loc, powfn, 2, arg00, narg01);
	    }
	}
    }
  return NULL_TREE;
}
