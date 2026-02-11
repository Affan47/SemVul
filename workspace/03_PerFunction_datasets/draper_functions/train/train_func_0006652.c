gen_split_1746 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx operand0;
  rtx operand1;
  rtx operand2;
  rtx operand3;
  rtx operand4;
  rtx operand5;
  rtx _val = 0;
  start_sequence ();
#line 8235 "../../src/gcc/config/rs6000/rs6000.md"

{
  rtx i3,i4;

  if (GET_CODE (operands[2]) == CONST_DOUBLE)
    {
      HOST_WIDE_INT value = CONST_DOUBLE_LOW (operands[2]);
      i3 = immed_double_const (value & (~ (HOST_WIDE_INT) 0xffff),
					0, DImode);
      i4 = GEN_INT (value & 0xffff);
    }
  else
    {
      i3 = GEN_INT (INTVAL (operands[2])
			     & (~ (HOST_WIDE_INT) 0xffff));
      i4 = GEN_INT (INTVAL (operands[2]) & 0xffff);
    }
  operands[4] = gen_rtx_fmt_ee (GET_CODE (operands[3]), DImode,
				operands[1], i3);
  operands[5] = gen_rtx_fmt_ee (GET_CODE (operands[3]), DImode,
				operands[0], i4);
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
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	operand4));
  emit_insn (gen_rtx_SET (VOIDmode,
	copy_rtx (operand0),
	operand5));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
