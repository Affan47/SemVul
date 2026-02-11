gen_rotrhi3 (operand0, operand1, operand2)
     rtx operand0;
     rtx operand1;
     rtx operand2;
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[3];
    operands[0] = operand0;
    operands[1] = operand1;
    operands[2] = operand2;

{
  if (GET_CODE (operands[2]) != CONST_INT)
    {
      rtx scratch = gen_reg_rtx (HImode);
      operand1 = force_reg (HImode, operand1);

      emit_move_insn (scratch, operands[2]);
      emit_insn (gen_rtx (PARALLEL, VOIDmode,
		 gen_rtvec (2, gen_rtx (SET, VOIDmode,
					operand0,
					gen_rtx_ROTATERT (HImode,
						operand1, scratch)),
			      gen_rtx (CLOBBER, VOIDmode, scratch))));
      DONE;
    }
}
    operand0 = operands[0];
    operand1 = operands[1];
    operand2 = operands[2];
  }
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	gen_rtx_ROTATERT (HImode,
	operand1,
	operand2)));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
