gen_clzdi2 (rtx operand0,
	rtx operand1)
{
  rtx operand2;
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[3];
    operands[0] = operand0;
    operands[1] = operand1;
#line 12048 "../../src/gcc/config/i386/i386.md"
{
  if (TARGET_ABM)
    {
      emit_insn (gen_clzdi2_abm (operands[0], operands[1]));
      DONE;
    }
  operands[2] = GEN_INT (GET_MODE_BITSIZE (DImode)-1);
}
    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
    operand2 = operands[2];
    (void) operand2;
  }
  emit (gen_rtx_PARALLEL (VOIDmode,
	gen_rtvec (2,
		gen_rtx_SET (VOIDmode,
	operand0,
	gen_rtx_MINUS (DImode,
	operand2,
	gen_rtx_CLZ (DImode,
	operand1))),
		gen_hard_reg_clobber (CCmode, 17))));
  emit (gen_rtx_PARALLEL (VOIDmode,
	gen_rtvec (2,
		gen_rtx_SET (VOIDmode,
	copy_rtx (operand0),
	gen_rtx_XOR (DImode,
	copy_rtx (operand0),
	copy_rtx (operand2))),
		gen_hard_reg_clobber (CCmode, 17))));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
