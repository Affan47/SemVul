gen_fix_truncv4sfv4si2 (rtx operand0,
	rtx operand1)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[2];
    operands[0] = operand0;
    operands[1] = operand1;
#line 769 "../../src/gcc/config/rs6000/vector.md"

{
  if (V4SFmode == V4SFmode && VECTOR_UNIT_ALTIVEC_P (V4SFmode))
    {
      emit_insn (gen_altivec_vctsxs (operands[0], operands[1], const0_rtx));
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
	gen_rtx_FIX (V4SImode,
	operand1)));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
