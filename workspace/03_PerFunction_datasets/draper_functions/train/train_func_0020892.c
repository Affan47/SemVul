gen_extendsidi2 (rtx operand0,
	rtx operand1)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[2];
    operands[0] = operand0;
    operands[1] = operand1;
#line 3828 "../../src/gcc/config/i386/i386.md"
{
  if (!TARGET_64BIT)
    {
      emit_insn (gen_extendsidi2_1 (operands[0], operands[1]));
      DONE;
    }
}
    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
  }
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	gen_rtx_SIGN_EXTEND (DImode,
	operand1)));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
