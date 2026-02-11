fold_trunc_transparent_mathfn (location_t loc, tree fndecl, tree arg)
{
  enum built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  if (!validate_arg (arg, REAL_TYPE))
    return NULL_TREE;


  if (fcode == builtin_mathfn_code (arg))
    return arg;


  if (! flag_errno_math && integer_valued_real_p (arg))
    return arg;

  if (optimize)
    {
      tree arg0 = strip_float_extensions (arg);
      tree ftype = TREE_TYPE (TREE_TYPE (fndecl));
      tree newtype = TREE_TYPE (arg0);
      tree decl;

      if (TYPE_PRECISION (newtype) < TYPE_PRECISION (ftype)
	  && (decl = mathfn_built_in (newtype, fcode)))
	return fold_convert_loc (loc, ftype,
				 build_call_expr_loc (loc, decl, 1,
						  fold_convert_loc (loc,
								    newtype,
								    arg0)));
    }
  return NULL_TREE;
}
