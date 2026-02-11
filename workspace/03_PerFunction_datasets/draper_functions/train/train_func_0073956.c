fold_builtin_ceil (tree exp)
{
  tree arglist = TREE_OPERAND (exp, 1);
  tree arg;

  if (! validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    return 0;


  arg = TREE_VALUE (arglist);
  if (TREE_CODE (arg) == REAL_CST && ! TREE_CONSTANT_OVERFLOW (arg))
    {
      REAL_VALUE_TYPE x;

      x = TREE_REAL_CST (arg);
      if (! REAL_VALUE_ISNAN (x) || ! flag_errno_math)
	{
	  tree type = TREE_TYPE (exp);
	  REAL_VALUE_TYPE r;

	  real_ceil (&r, TYPE_MODE (type), &x);
	  return build_real (type, r);
	}
    }

  return fold_trunc_transparent_mathfn (exp);
}
