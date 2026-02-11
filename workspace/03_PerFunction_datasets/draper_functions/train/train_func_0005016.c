thumb1_emit_multi_reg_push (unsigned long mask, unsigned long real_regs)
{
  unsigned long regno;
  rtx par[10], tmp, reg, insn;
  int i, j;


  for (i = 0; mask; ++i, mask &= mask - 1)
    {
      regno = ctz_hwi (mask);
      reg = gen_rtx_REG (SImode, regno);

      if (i == 0)
	tmp = gen_rtx_UNSPEC (BLKmode, gen_rtvec (1, reg), UNSPEC_PUSH_MULT);
      else
	tmp = gen_rtx_USE (VOIDmode, reg);

      par[i] = tmp;
    }

  tmp = plus_constant (stack_pointer_rtx, -4 * i);
  tmp = gen_rtx_PRE_MODIFY (Pmode, stack_pointer_rtx, tmp);
  tmp = gen_frame_mem (BLKmode, tmp);
  tmp = gen_rtx_SET (VOIDmode, tmp, par[0]);
  par[0] = tmp;

  tmp = gen_rtx_PARALLEL (VOIDmode, gen_rtvec_v (i, par));
  insn = emit_insn (tmp);


  tmp = plus_constant (stack_pointer_rtx, -4 * i);
  tmp = gen_rtx_SET (VOIDmode, stack_pointer_rtx, tmp);
  par[0] = tmp;


  for (j = 0; real_regs; ++j, real_regs &= real_regs - 1)
    {
      regno = ctz_hwi (real_regs);
      reg = gen_rtx_REG (SImode, regno);

      tmp = plus_constant (stack_pointer_rtx, j * 4);
      tmp = gen_frame_mem (SImode, tmp);
      tmp = gen_rtx_SET (VOIDmode, tmp, reg);
      RTX_FRAME_RELATED_P (tmp) = 1;
      par[j + 1] = tmp;
    }

  if (j == 0)
    tmp = par[0];
  else
    {
      RTX_FRAME_RELATED_P (par[0]) = 1;
      tmp = gen_rtx_SEQUENCE (VOIDmode, gen_rtvec_v (j + 1, par));
    }

  add_reg_note (insn, REG_FRAME_RELATED_EXPR, tmp);

  return insn;
}
