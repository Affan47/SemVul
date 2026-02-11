gen_split_2210 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx operand0;
  rtx operand1;
  rtx operand2;
  rtx _val = 0;
  start_sequence ();
#line 3559 "../../src/gcc/config/i386/i386.md"
{
  rtx c = operands[2];
  rtx r = operands[0];

  if (GET_CODE (r) == SUBREG)
    r = SUBREG_REG (r);

  if (SSE_REG_P (r))
    {
      if (!standard_sse_constant_p (c))
	FAIL;
    }
  else if (FP_REG_P (r))
    {
      if (standard_80387_constant_p (c) < 1)
	FAIL;
    }
  else if (MMX_REG_P (r))
    FAIL;
}
  operand0 = operands[0];
  (void) operand0;
  operand1 = operands[1];
  (void) operand1;
  operand2 = operands[2];
  (void) operand2;
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	operand2));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
