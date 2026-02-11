gen_split_2155 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx operand0;
  rtx operand1;
  rtx operand2;
  rtx operand3;
  rtx _val = 0;
  start_sequence ();
#line 5842 "../../src/gcc/config/arm/arm.md"
operands[3] = can_create_pseudo_p () ? gen_reg_rtx (SImode) : operands[0];
  operand0 = operands[0];
  (void) operand0;
  operand1 = operands[1];
  (void) operand1;
  operand2 = operands[2];
  (void) operand2;
  operand3 = operands[3];
  (void) operand3;
  emit_insn (gen_rtx_SET (VOIDmode,
	operand3,
	gen_rtx_UNSPEC (SImode,
	gen_rtvec (1,
		operand2),
	3)));
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	gen_rtx_MEM (SImode,
	gen_rtx_PLUS (SImode,
	operand1,
	copy_rtx (operand3)))));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
