gen_split_2233 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx operand0;
  rtx operand1;
  rtx operand2;
  rtx operand3;
  rtx operand4;
  rtx operand5;
  rtx operand6;
  rtx operand7;
  rtx _val = 0;
  start_sequence ();
#line 10936 "../../src/gcc/config/arm/arm.md"

  {
    enum machine_mode mode = SELECT_CC_MODE (GET_CODE (operands[1]),
					     operands[2], operands[3]);
    enum rtx_code rc = GET_CODE (operands[1]);

    operands[5] = gen_rtx_REG (mode, CC_REGNUM);
    operands[6] = gen_rtx_COMPARE (mode, operands[2], operands[3]);
    if (mode == CCFPmode || mode == CCFPEmode)
      rc = reverse_condition_maybe_unordered (rc);
    else
      rc = reverse_condition (rc);

    operands[7] = gen_rtx_fmt_ee (rc, VOIDmode, operands[5], const0_rtx);
  }
  operand0 = operands[0];
  (void) operand0;
  operand1 = operands[1];
  (void) operand1;
  operand2 = operands[2];
  (void) operand2;
  operand3 = operands[3];
  (void) operand3;
  operand4 = operands[4];
  (void) operand4;
  operand5 = operands[5];
  (void) operand5;
  operand6 = operands[6];
  (void) operand6;
  operand7 = operands[7];
  (void) operand7;
  emit_insn (gen_rtx_SET (VOIDmode,
	operand5,
	operand6));
  emit_insn (gen_rtx_COND_EXEC (VOIDmode,
	operand7,
	gen_rtx_SET (VOIDmode,
	operand0,
	operand4)));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
