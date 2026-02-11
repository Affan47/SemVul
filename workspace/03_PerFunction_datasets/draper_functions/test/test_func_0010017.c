fix_lexical_addr (rtx addr, tree var)
{
  rtx basereg;
  HOST_WIDE_INT displacement;
  tree context = decl_function_context (var);
  struct function *fp;
  rtx base = 0;


  if (context == current_function_decl || context == inline_function_decl)
    return addr;

  fp = find_function_data (context);

  if (GET_CODE (addr) == ADDRESSOF && GET_CODE (XEXP (addr, 0)) == MEM)
    addr = XEXP (XEXP (addr, 0), 0);


  if (GET_CODE (addr) == REG)
    basereg = addr, displacement = 0;
  else if (GET_CODE (addr) == PLUS && GET_CODE (XEXP (addr, 1)) == CONST_INT)
    basereg = XEXP (addr, 0), displacement = INTVAL (XEXP (addr, 1));
  else
    abort ();


  if (basereg == fp->internal_arg_pointer)
    {


#ifdef NEED_SEPARATE_AP
      rtx addr;

      addr = get_arg_pointer_save_area (fp);
      addr = fix_lexical_addr (XEXP (addr, 0), var);
      addr = memory_address (Pmode, addr);

      base = gen_rtx_MEM (Pmode, addr);
      set_mem_alias_set (base, get_frame_alias_set ());
      base = copy_to_reg (base);
#else
      displacement += (FIRST_PARM_OFFSET (context) - STARTING_FRAME_OFFSET);
      base = lookup_static_chain (var);
#endif
    }

  else if (basereg == virtual_stack_vars_rtx)
    {


      tree link;

      for (link = context_display; link; link = TREE_CHAIN (link))
	if (TREE_PURPOSE (link) == context)
	  {
	    base = RTL_EXPR_RTL (TREE_VALUE (link));
	    break;
	  }
    }

  if (base == 0)
    abort ();


  return plus_constant (base, displacement);
}
