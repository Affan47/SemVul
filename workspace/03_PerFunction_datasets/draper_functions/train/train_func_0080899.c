gen_call_value (rtx operand0,
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
#line 1557 "/home/dcharvest/ubuntu64-builder/genericMake/build/toolchain/dl/gcc-4.7.4/gcc/config/xtensa/xtensa.md"
{
  rtx addr = XEXP (operands[1], 0);
  if (flag_pic && GET_CODE (addr) == SYMBOL_REF
      && (!SYMBOL_REF_LOCAL_P (addr) || SYMBOL_REF_EXTERNAL_P (addr)))
    addr = gen_sym_PLT (addr);
  if (!call_insn_operand (addr, VOIDmode))
    XEXP (operands[1], 0) = copy_to_mode_reg (Pmode, addr);
}
    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
    operand2 = operands[2];
    (void) operand2;
  }
  emit_call_insn (gen_rtx_SET (VOIDmode,
	operand0,
	gen_rtx_CALL (VOIDmode,
	operand1,
	operand2)));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
