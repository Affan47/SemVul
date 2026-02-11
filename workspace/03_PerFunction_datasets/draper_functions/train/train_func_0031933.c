check_narrowing (tree type, tree init)
{
  tree ftype = unlowered_expr_type (init);
  bool ok = true;
  REAL_VALUE_TYPE d;

  if (!warn_narrowing || !ARITHMETIC_TYPE_P (type))
    return;

  if (BRACE_ENCLOSED_INITIALIZER_P (init)
      && TREE_CODE (type) == COMPLEX_TYPE)
    {
      tree elttype = TREE_TYPE (type);
      check_narrowing (elttype, CONSTRUCTOR_ELT (init, 0)->value);
      if (CONSTRUCTOR_NELTS (init) > 1)
	check_narrowing (elttype, CONSTRUCTOR_ELT (init, 1)->value);
      return;
    }

  init = maybe_constant_value (init);

  if (TREE_CODE (type) == INTEGER_TYPE
      && TREE_CODE (ftype) == REAL_TYPE)
    ok = false;
  else if (INTEGRAL_OR_ENUMERATION_TYPE_P (ftype)
	   && CP_INTEGRAL_TYPE_P (type))
    {
      if (TREE_CODE (ftype) == ENUMERAL_TYPE)

	ftype = ENUM_UNDERLYING_TYPE (ftype);
      if ((tree_int_cst_lt (TYPE_MAX_VALUE (type),
			    TYPE_MAX_VALUE (ftype))
	   || tree_int_cst_lt (TYPE_MIN_VALUE (ftype),
			       TYPE_MIN_VALUE (type)))
	  && (TREE_CODE (init) != INTEGER_CST
	      || !int_fits_type_p (init, type)))
	ok = false;
    }
  else if (TREE_CODE (ftype) == REAL_TYPE
	   && TREE_CODE (type) == REAL_TYPE)
    {
      if (TYPE_PRECISION (type) < TYPE_PRECISION (ftype))
	{
	  if (TREE_CODE (init) == REAL_CST)
	    {


	      REAL_VALUE_TYPE r;
	      d = TREE_REAL_CST (init);
	      real_convert (&r, TYPE_MODE (type), &d);
	      if (real_isinf (&r))
		ok = false;
	    }
	  else
	    ok = false;
	}
    }
  else if (INTEGRAL_OR_ENUMERATION_TYPE_P (ftype)
	   && TREE_CODE (type) == REAL_TYPE)
    {
      ok = false;
      if (TREE_CODE (init) == INTEGER_CST)
	{
	  d = real_value_from_int_cst (0, init);
	  if (exact_real_truncate (TYPE_MODE (type), &d))
	    ok = true;
	}
    }

  if (!ok)
    {
      if (cxx_dialect >= cxx0x)
	pedwarn (EXPR_LOC_OR_HERE (init), OPT_Wnarrowing,
		 "narrowing conversion of %qE from %qT to %qT inside { }",
		 init, ftype, type);
      else
	warning_at (EXPR_LOC_OR_HERE (init), OPT_Wnarrowing,
		    "narrowing conversion of %qE from %qT to %qT inside { } "
		    "is ill-formed in C++11", init, ftype, type);
    }
}
