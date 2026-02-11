gen_reduc_splus_v4sf (rtx operand0,
	rtx operand1)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[2];
    operands[0] = operand0;
    operands[1] = operand1;
#line 1454 "../../src/gcc/config/i386/sse.md"
{
  if (TARGET_SSE3)
    {
      rtx tmp = gen_reg_rtx (V4SFmode);
      emit_insn (gen_sse3_haddv4sf3 (tmp, operands[1], operands[1]));
      emit_insn (gen_sse3_haddv4sf3 (operands[0], tmp, tmp));
    }
  else
    ix86_expand_reduc_v4sf (gen_addv4sf3, operands[0], operands[1]);
  DONE;
}
    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
  }
  emit (operand0);
  emit (operand1);
  _val = get_insns ();
  end_sequence ();
  return _val;
}
