gen_ilogbdf2 (rtx operand0,
	rtx operand1)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[2];
    operands[0] = operand0;
    operands[1] = operand1;
#line 14204 "../../src/gcc/config/i386/i386.md"
{
  rtx op0, op1;

  if (optimize_insn_for_size_p ())
    FAIL;

  op0 = gen_reg_rtx (XFmode);
  op1 = gen_reg_rtx (XFmode);

  emit_insn (gen_fxtract_extenddfxf3_i387 (op0, op1, operands[1]));
  emit_insn (gen_fix_truncxfsi2 (operands[0], op1));
  DONE;
}
    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
  }
  emit_insn (gen_rtx_USE (VOIDmode,
	operand0));
  emit_insn (gen_rtx_USE (VOIDmode,
	operand1));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
