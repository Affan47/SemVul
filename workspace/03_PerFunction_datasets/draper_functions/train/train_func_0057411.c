gen_cbranchsi4 (rtx operand0,
	rtx operand1,
	rtx operand2,
	rtx operand3)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[4];
    operands[0] = operand0;
    operands[1] = operand1;
    operands[2] = operand2;
    operands[3] = operand3;
#line 12946 "../../src/gcc/config/rs6000/rs6000.md"

{


  if (GET_CODE (operands[2]) == CONST_INT
      && INTVAL (operands[2]) < 0)
    {
      operands[2] = force_reg (SImode, operands[2]);
      operands[0] = gen_rtx_fmt_ee (GET_CODE (operands[0]),
				    GET_MODE (operands[0]),
				    operands[1], operands[2]);
   }

  rs6000_emit_cbranch (SImode, operands);
  DONE;
}
    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
    operand2 = operands[2];
    (void) operand2;
    operand3 = operands[3];
    (void) operand3;
  }
  emit_insn (gen_rtx_USE (VOIDmode,
	gen_rtx_fmt_ee (GET_CODE (operand0), VOIDmode,
		operand1,
		operand2)));
  emit_insn (gen_rtx_USE (VOIDmode,
	operand3));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
