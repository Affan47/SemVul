gen_addsi3 (rtx operand0,
	rtx operand1,
	rtx operand2)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[3];
    operands[0] = operand0;
    operands[1] = operand1;
    operands[2] = operand2;
#line 721 "../../src/gcc/config/arm/arm.md"

  if (TARGET_32BIT && GET_CODE (operands[2]) == CONST_INT)
    {
      arm_split_constant (PLUS, SImode, NULL_RTX,
	                  INTVAL (operands[2]), operands[0], operands[1],
			  optimize && can_create_pseudo_p ());
      DONE;
    }

    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
    operand2 = operands[2];
    (void) operand2;
  }
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	gen_rtx_PLUS (SImode,
	operand1,
	operand2)));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
