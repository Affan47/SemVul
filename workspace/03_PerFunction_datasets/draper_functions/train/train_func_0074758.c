fold_builtin_memory_chk (location_t loc, tree fndecl,
			 tree dest, tree src, tree len, tree size,
			 tree maxlen, bool ignore,
			 enum built_in_function fcode)
{
  tree fn;

  if (!validate_arg (dest, POINTER_TYPE)
      || !validate_arg (src,
			(fcode == BUILT_IN_MEMSET_CHK
			 ? INTEGER_TYPE : POINTER_TYPE))
      || !validate_arg (len, INTEGER_TYPE)
      || !validate_arg (size, INTEGER_TYPE))
    return NULL_TREE;


  if (fcode != BUILT_IN_MEMSET_CHK && operand_equal_p (src, dest, 0))
    {
      if (fcode != BUILT_IN_MEMPCPY_CHK)
	return omit_one_operand_loc (loc, TREE_TYPE (TREE_TYPE (fndecl)),
				 dest, len);
      else
	{
	  tree temp = fold_build_pointer_plus_loc (loc, dest, len);
	  return fold_convert_loc (loc, TREE_TYPE (TREE_TYPE (fndecl)), temp);
	}
    }

  if (! host_integerp (size, 1))
    return NULL_TREE;

  if (! integer_all_onesp (size))
    {
      if (! host_integerp (len, 1))
	{


	  if (maxlen == NULL_TREE || ! host_integerp (maxlen, 1))
	    {
	      if (fcode == BUILT_IN_MEMPCPY_CHK && ignore)
		{


		  fn = builtin_decl_explicit (BUILT_IN_MEMCPY_CHK);
		  if (!fn)
		    return NULL_TREE;

		  return build_call_expr_loc (loc, fn, 4, dest, src, len, size);
		}
	      return NULL_TREE;
	    }
	}
      else
	maxlen = len;

      if (tree_int_cst_lt (size, maxlen))
	return NULL_TREE;
    }

  fn = NULL_TREE;


  switch (fcode)
    {
    case BUILT_IN_MEMCPY_CHK:
      fn = builtin_decl_explicit (BUILT_IN_MEMCPY);
      break;
    case BUILT_IN_MEMPCPY_CHK:
      fn = builtin_decl_explicit (BUILT_IN_MEMPCPY);
      break;
    case BUILT_IN_MEMMOVE_CHK:
      fn = builtin_decl_explicit (BUILT_IN_MEMMOVE);
      break;
    case BUILT_IN_MEMSET_CHK:
      fn = builtin_decl_explicit (BUILT_IN_MEMSET);
      break;
    default:
      break;
    }

  if (!fn)
    return NULL_TREE;

  return build_call_expr_loc (loc, fn, 3, dest, src, len);
}
