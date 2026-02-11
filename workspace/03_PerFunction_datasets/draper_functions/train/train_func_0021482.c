gen_exp10xf2 (rtx operand0,
	rtx operand1)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[2];
    operands[0] = operand0;
    operands[1] = operand1;
#line 14314 "../../src/gcc/config/i386/i386.md"
{
  rtx op2;

  if (optimize_insn_for_size_p ())
    FAIL;

  op2 = gen_reg_rtx (XFmode);
  emit_move_insn (op2, standard_80387_constant_rtx (6));

  emit_insn (gen_expNcorexf3 (operands[0], operands[1], op2));
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
