expand_debug_source_expr (tree exp)
{
  rtx op0 = NULL_RTX;
  enum machine_mode mode = VOIDmode, inner_mode;

  switch (TREE_CODE (exp))
    {
    case PARM_DECL:
      {
	mode = DECL_MODE (exp);
	op0 = expand_debug_parm_decl (exp);
	if (op0)
	   break;


	if (!DECL_RTL_SET_P (exp)
	    && !DECL_INCOMING_RTL (exp)
	    && DECL_ABSTRACT_ORIGIN (current_function_decl))
	  {
	    tree aexp = exp;
	    if (DECL_ABSTRACT_ORIGIN (exp))
	      aexp = DECL_ABSTRACT_ORIGIN (exp);
	    if (DECL_CONTEXT (aexp)
		== DECL_ABSTRACT_ORIGIN (current_function_decl))
	      {
		VEC(tree, gc) **debug_args;
		unsigned int ix;
		tree ddecl;
#ifdef ENABLE_CHECKING
		tree parm;
		for (parm = DECL_ARGUMENTS (current_function_decl);
		     parm; parm = DECL_CHAIN (parm))
		  gcc_assert (parm != exp
			      && DECL_ABSTRACT_ORIGIN (parm) != aexp);
#endif
		debug_args = decl_debug_args_lookup (current_function_decl);
		if (debug_args != NULL)
		  {
		    for (ix = 0; VEC_iterate (tree, *debug_args, ix, ddecl);
			 ix += 2)
		      if (ddecl == aexp)
			return gen_rtx_DEBUG_PARAMETER_REF (mode, aexp);
		  }
	      }
	  }
	break;
      }
    default:
      break;
    }

  if (op0 == NULL_RTX)
    return NULL_RTX;

  inner_mode = GET_MODE (op0);
  if (mode == inner_mode)
    return op0;

  if (FLOAT_MODE_P (mode) && FLOAT_MODE_P (inner_mode))
    {
      if (GET_MODE_BITSIZE (mode) == GET_MODE_BITSIZE (inner_mode))
	op0 = simplify_gen_subreg (mode, op0, inner_mode, 0);
      else if (GET_MODE_BITSIZE (mode) < GET_MODE_BITSIZE (inner_mode))
	op0 = simplify_gen_unary (FLOAT_TRUNCATE, mode, op0, inner_mode);
      else
	op0 = simplify_gen_unary (FLOAT_EXTEND, mode, op0, inner_mode);
    }
  else if (FLOAT_MODE_P (mode))
    gcc_unreachable ();
  else if (FLOAT_MODE_P (inner_mode))
    {
      if (TYPE_UNSIGNED (TREE_TYPE (exp)))
	op0 = simplify_gen_unary (UNSIGNED_FIX, mode, op0, inner_mode);
      else
	op0 = simplify_gen_unary (FIX, mode, op0, inner_mode);
    }
  else if (CONSTANT_P (op0)
	   || GET_MODE_BITSIZE (mode) <= GET_MODE_BITSIZE (inner_mode))
    op0 = simplify_gen_subreg (mode, op0, inner_mode,
			       subreg_lowpart_offset (mode, inner_mode));
  else if (TYPE_UNSIGNED (TREE_TYPE (exp)))
    op0 = simplify_gen_unary (ZERO_EXTEND, mode, op0, inner_mode);
  else
    op0 = simplify_gen_unary (SIGN_EXTEND, mode, op0, inner_mode);

  return op0;
}
