small_call_insn_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  if (GET_CODE (op) == MEM)
    {
      rtx inside = XEXP (op, 0);


      if (register_operand (inside, Pmode))
	return 1;


      if (GET_CODE (inside) == SYMBOL_REF
	  && (SYMBOL_REF_FLAGS (inside) & SYMBOL_FLAG_FUNCVEC_FUNCTION))
	return 1;
    }

  return 0;
}
