push_block (rtx size, int extra, int below)
{
  rtx temp;

  size = convert_modes (Pmode, ptr_mode, size, 1);
  if (CONSTANT_P (size))
    anti_adjust_stack (plus_constant (Pmode, size, extra));
  else if (REG_P (size) && extra == 0)
    anti_adjust_stack (size);
  else
    {
      temp = copy_to_mode_reg (Pmode, size);
      if (extra != 0)
	temp = expand_binop (Pmode, add_optab, temp, GEN_INT (extra),
			     temp, 0, OPTAB_LIB_WIDEN);
      anti_adjust_stack (temp);
    }

#ifndef STACK_GROWS_DOWNWARD
  if (0)
#else
  if (1)
#endif
    {
      temp = virtual_outgoing_args_rtx;
      if (extra != 0 && below)
	temp = plus_constant (Pmode, temp, extra);
    }
  else
    {
      if (CONST_INT_P (size))
	temp = plus_constant (Pmode, virtual_outgoing_args_rtx,
			      -INTVAL (size) - (below ? 0 : extra));
      else if (extra != 0 && !below)
	temp = gen_rtx_PLUS (Pmode, virtual_outgoing_args_rtx,
			     negate_rtx (Pmode, plus_constant (Pmode, size,
							       extra)));
      else
	temp = gen_rtx_PLUS (Pmode, virtual_outgoing_args_rtx,
			     negate_rtx (Pmode, size));
    }

  return memory_address (GET_CLASS_NARROWEST_MODE (MODE_INT), temp);
}
