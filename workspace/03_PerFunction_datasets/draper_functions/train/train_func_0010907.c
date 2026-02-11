expand_builtin_memmove (tree arglist, rtx target, enum machine_mode mode)
{
  if (!validate_arglist (arglist,
			 POINTER_TYPE, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
    return 0;
  else
    {
      tree dest = TREE_VALUE (arglist);
      tree src = TREE_VALUE (TREE_CHAIN (arglist));
      tree len = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));

      unsigned int src_align = get_pointer_alignment (src, BIGGEST_ALIGNMENT);
      unsigned int dest_align
	= get_pointer_alignment (dest, BIGGEST_ALIGNMENT);


      if (dest_align == 0)
	return 0;


      if (integer_zerop (len))
	{

	  expand_expr (src, const0_rtx, VOIDmode, EXPAND_NORMAL);
	  return expand_expr (dest, target, mode, EXPAND_NORMAL);
	}


      if (operand_equal_p (src, dest, 0))
	{

	  expand_expr (len, const0_rtx, VOIDmode, EXPAND_NORMAL);
	  return expand_expr (dest, target, mode, EXPAND_NORMAL);
	}


      if (src_align == 0)
	return 0;


      if (readonly_data_expr (src))
        {
	  tree const fn = implicit_built_in_decls[BUILT_IN_MEMCPY];
	  if (!fn)
	    return 0;
	  return expand_expr (build_function_call_expr (fn, arglist),
			      target, mode, EXPAND_NORMAL);
	}


      return 0;
   }
}
