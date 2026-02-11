gen_doloop_end (rtx operand0,
	rtx operand1,
	rtx operand2,
	rtx operand3,
	rtx operand4,
	rtx operand5)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[6];
    operands[0] = operand0;
    operands[1] = operand1;
    operands[2] = operand2;
    operands[3] = operand3;
    operands[4] = operand4;
    operands[5] = operand5;
#line 14851 "../../src/gcc/config/rs6000/rs6000.md"

{

  if (INTVAL (operands[3]) > 1)
    FAIL;
  if (TARGET_64BIT)
    {
      if (GET_MODE (operands[0]) != DImode)
	FAIL;
      emit_jump_insn (gen_ctrdi (operands[0], operands[4]));
    }
  else
    {
      if (GET_MODE (operands[0]) != SImode)
	FAIL;
      emit_jump_insn (gen_ctrsi (operands[0], operands[4]));
    }
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
    operand4 = operands[4];
    (void) operand4;
    operand5 = operands[5];
    (void) operand5;
  }
  emit_insn (gen_rtx_USE (VOIDmode,
	operand0));
  emit_insn (gen_rtx_USE (VOIDmode,
	operand1));
  emit_insn (gen_rtx_USE (VOIDmode,
	operand2));
  emit_insn (gen_rtx_USE (VOIDmode,
	operand3));
  emit_insn (gen_rtx_USE (VOIDmode,
	operand4));
  emit_insn (gen_rtx_USE (VOIDmode,
	operand5));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
