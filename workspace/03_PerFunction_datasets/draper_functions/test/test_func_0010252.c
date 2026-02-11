expand_builtin_memset (tree arglist, rtx target, enum machine_mode mode)
{
  if (!validate_arglist (arglist,
			 POINTER_TYPE, INTEGER_TYPE, INTEGER_TYPE, VOID_TYPE))
    return 0;
  else
    {
      tree dest = TREE_VALUE (arglist);
      tree val = TREE_VALUE (TREE_CHAIN (arglist));
      tree len = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));
      char c;

      unsigned int dest_align
	= get_pointer_alignment (dest, BIGGEST_ALIGNMENT);
      rtx dest_mem, dest_addr, len_rtx;


      if (dest_align == 0)
	return 0;


      if (integer_zerop (len))
	{

	  expand_expr (val, const0_rtx, VOIDmode, EXPAND_NORMAL);
	  return expand_expr (dest, target, mode, EXPAND_NORMAL);
	}

      if (TREE_CODE (val) != INTEGER_CST)
	{
	  rtx val_rtx;

	  if (!host_integerp (len, 1))
	    return 0;

	  if (optimize_size && tree_low_cst (len, 1) > 1)
	    return 0;


	  c = 1;
	  if (!can_store_by_pieces (tree_low_cst (len, 1),
				    builtin_memset_read_str,
				    &c, dest_align))
	    return 0;

	  val = fold (build1 (CONVERT_EXPR, unsigned_char_type_node, val));
	  val_rtx = expand_expr (val, NULL_RTX, VOIDmode, 0);
	  val_rtx = force_reg (TYPE_MODE (unsigned_char_type_node),
			       val_rtx);
	  dest_mem = get_memory_rtx (dest);
	  store_by_pieces (dest_mem, tree_low_cst (len, 1),
			   builtin_memset_gen_str,
			   val_rtx, dest_align, 0);
	  dest_mem = force_operand (XEXP (dest_mem, 0), NULL_RTX);
	  dest_mem = convert_memory_address (ptr_mode, dest_mem);
	  return dest_mem;
	}

      if (target_char_cast (val, &c))
	return 0;

      if (c)
	{
	  if (!host_integerp (len, 1))
	    return 0;
	  if (!can_store_by_pieces (tree_low_cst (len, 1),
				    builtin_memset_read_str, &c,
				    dest_align))
	    return 0;

	  dest_mem = get_memory_rtx (dest);
	  store_by_pieces (dest_mem, tree_low_cst (len, 1),
			   builtin_memset_read_str,
			   &c, dest_align, 0);
	  dest_mem = force_operand (XEXP (dest_mem, 0), NULL_RTX);
	  dest_mem = convert_memory_address (ptr_mode, dest_mem);
	  return dest_mem;
	}

      len_rtx = expand_expr (len, NULL_RTX, VOIDmode, 0);

      dest_mem = get_memory_rtx (dest);
      set_mem_align (dest_mem, dest_align);
      dest_addr = clear_storage (dest_mem, len_rtx);

      if (dest_addr == 0)
	{
	  dest_addr = force_operand (XEXP (dest_mem, 0), NULL_RTX);
	  dest_addr = convert_memory_address (ptr_mode, dest_addr);
	}

      return dest_addr;
    }
}
