assign_parm_find_stack_rtl (tree parm, struct assign_parm_data_one *data)
{
  rtx offset_rtx, stack_parm;
  unsigned int align, boundary;


  if (data->entry_parm)
    offset_rtx = ARGS_SIZE_RTX (data->locate.slot_offset);
  else
    offset_rtx = ARGS_SIZE_RTX (data->locate.offset);

  stack_parm = crtl->args.internal_arg_pointer;
  if (offset_rtx != const0_rtx)
    stack_parm = gen_rtx_PLUS (Pmode, stack_parm, offset_rtx);
  stack_parm = gen_rtx_MEM (data->promoted_mode, stack_parm);

  if (!data->passed_pointer)
    {
      set_mem_attributes (stack_parm, parm, 1);


      if (data->promoted_mode != BLKmode
	  && data->promoted_mode != DECL_MODE (parm))
	{
	  set_mem_size (stack_parm,
			GEN_INT (GET_MODE_SIZE (data->promoted_mode)));
	  if (MEM_EXPR (stack_parm) && MEM_OFFSET (stack_parm))
	    {
	      int offset = subreg_lowpart_offset (DECL_MODE (parm),
						  data->promoted_mode);
	      if (offset)
		set_mem_offset (stack_parm,
				plus_constant (MEM_OFFSET (stack_parm),
					       -offset));
	    }
	}
    }

  boundary = data->locate.boundary;
  align = BITS_PER_UNIT;


  if (data->locate.where_pad != downward || data->entry_parm)
    align = boundary;
  else if (CONST_INT_P (offset_rtx))
    {
      align = INTVAL (offset_rtx) * BITS_PER_UNIT | boundary;
      align = align & -align;
    }
  set_mem_align (stack_parm, align);

  if (data->entry_parm)
    set_reg_attrs_for_parm (data->entry_parm, stack_parm);

  data->stack_parm = stack_parm;
}
