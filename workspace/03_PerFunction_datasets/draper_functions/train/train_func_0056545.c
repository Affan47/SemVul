gen_split_1688 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands ATTRIBUTE_UNUSED)
{
  rtx _val = 0;
  start_sequence ();
#line 6180 "../../src/gcc/config/rs6000/rs6000.md"
{
  rtx dest = operands[0];
  rtx src = operands[1];
  rtx tmp1 = operands[2];
  rtx tmp2 = operands[3];
  rtx stack = rs6000_allocate_stack_temp (SImode, false, true);

  if (GET_CODE (tmp1) == SCRATCH)
    tmp1 = gen_reg_rtx (DImode);
  if (GET_CODE (tmp2) == SCRATCH)
    tmp2 = gen_reg_rtx (DImode);

  emit_insn (gen_fctiwz_df (tmp1, src));
  emit_insn (gen_stfiwx (stack, tmp1));
  emit_insn (gen_lfiwax (tmp2, stack));
  emit_insn (gen_floatdidf2 (dest, tmp2));
  DONE;
}
  emit_insn (pc_rtx);
  _val = get_insns ();
  end_sequence ();
  return _val;
}
