gen_split_2498 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx operand0;
  rtx operand1;
  rtx operand2;
  rtx operand3;
  rtx _val = 0;
  start_sequence ();
#line 8823 "../../src/gcc/config/i386/i386.md"
{
  enum machine_mode mode = GET_MODE (operands[0]);
  enum machine_mode vmode = GET_MODE (operands[2]);
  rtx tmp;

  operands[0] = simplify_gen_subreg (vmode, operands[0], mode, 0);
  operands[1] = simplify_gen_subreg (vmode, operands[1], mode, 0);
  if (operands_match_p (operands[0], operands[2]))
    {
      tmp = operands[1];
      operands[1] = operands[2];
      operands[2] = tmp;
    }
  if (GET_CODE (operands[3]) == ABS)
    tmp = gen_rtx_AND (vmode, operands[1], operands[2]);
  else
    tmp = gen_rtx_XOR (vmode, operands[1], operands[2]);
  operands[3] = tmp;
}
  operand0 = operands[0];
  (void) operand0;
  operand1 = operands[1];
  (void) operand1;
  operand2 = operands[2];
  (void) operand2;
  operand3 = operands[3];
  (void) operand3;
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	operand3));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
