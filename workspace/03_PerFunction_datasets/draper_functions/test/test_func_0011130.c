array_value_type (gimple swtch, tree type, int num,
		  struct switch_conv_info *info)
{
  unsigned int i, len = vec_safe_length (info->constructors[num]);
  constructor_elt *elt;
  enum machine_mode mode;
  int sign = 0;
  tree smaller_type;

  if (!INTEGRAL_TYPE_P (type))
    return type;

  mode = GET_CLASS_NARROWEST_MODE (GET_MODE_CLASS (TYPE_MODE (type)));
  if (GET_MODE_SIZE (TYPE_MODE (type)) <= GET_MODE_SIZE (mode))
    return type;

  if (len < (optimize_bb_for_size_p (gimple_bb (swtch)) ? 2 : 32))
    return type;

  FOR_EACH_VEC_SAFE_ELT (info->constructors[num], i, elt)
    {
      double_int cst;

      if (TREE_CODE (elt->value) != INTEGER_CST)
	return type;

      cst = TREE_INT_CST (elt->value);
      while (1)
	{
	  unsigned int prec = GET_MODE_BITSIZE (mode);
	  if (prec > HOST_BITS_PER_WIDE_INT)
	    return type;

	  if (sign >= 0 && cst == cst.zext (prec))
	    {
	      if (sign == 0 && cst == cst.sext (prec))
		break;
	      sign = 1;
	      break;
	    }
	  if (sign <= 0 && cst == cst.sext (prec))
	    {
	      sign = -1;
	      break;
	    }

	  if (sign == 1)
	    sign = 0;

	  mode = GET_MODE_WIDER_MODE (mode);
	  if (mode == VOIDmode
	      || GET_MODE_SIZE (mode) >= GET_MODE_SIZE (TYPE_MODE (type)))
	    return type;
	}
    }

  if (sign == 0)
    sign = TYPE_UNSIGNED (type) ? 1 : -1;
  smaller_type = lang_hooks.types.type_for_mode (mode, sign >= 0);
  if (GET_MODE_SIZE (TYPE_MODE (type))
      <= GET_MODE_SIZE (TYPE_MODE (smaller_type)))
    return type;

  return smaller_type;
}
