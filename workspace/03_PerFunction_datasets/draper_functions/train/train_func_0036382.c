fold_builtin_bswap (tree fndecl, tree arg)
{
  if (! validate_arg (arg, INTEGER_TYPE))
    return NULL_TREE;


  if (TREE_CODE (arg) == INTEGER_CST && !TREE_OVERFLOW (arg))
    {
      HOST_WIDE_INT hi, width, r_hi = 0;
      unsigned HOST_WIDE_INT lo, r_lo = 0;
      tree type;

      type = TREE_TYPE (arg);
      width = TYPE_PRECISION (type);
      lo = TREE_INT_CST_LOW (arg);
      hi = TREE_INT_CST_HIGH (arg);

      switch (DECL_FUNCTION_CODE (fndecl))
	{
	  case BUILT_IN_BSWAP32:
	  case BUILT_IN_BSWAP64:
	    {
	      int s;

	      for (s = 0; s < width; s += 8)
		{
		  int d = width - s - 8;
		  unsigned HOST_WIDE_INT byte;

		  if (s < HOST_BITS_PER_WIDE_INT)
		    byte = (lo >> s) & 0xff;
		  else
		    byte = (hi >> (s - HOST_BITS_PER_WIDE_INT)) & 0xff;

		  if (d < HOST_BITS_PER_WIDE_INT)
		    r_lo |= byte << d;
		  else
		    r_hi |= byte << (d - HOST_BITS_PER_WIDE_INT);
		}
	    }

	    break;

	default:
	  gcc_unreachable ();
	}

      if (width < HOST_BITS_PER_WIDE_INT)
	return build_int_cst (TREE_TYPE (TREE_TYPE (fndecl)), r_lo);
      else
	return build_int_cst_wide (TREE_TYPE (TREE_TYPE (fndecl)), r_lo, r_hi);
    }

  return NULL_TREE;
}
