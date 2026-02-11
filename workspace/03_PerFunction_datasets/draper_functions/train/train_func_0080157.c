is_direct_call_opcode (xtensa_opcode opcode)
{
  xtensa_isa isa = xtensa_default_isa;
  int n, num_operands;

  if (xtensa_opcode_is_call (isa, opcode) != 1)
    return FALSE;

  num_operands = xtensa_opcode_num_operands (isa, opcode);
  for (n = 0; n < num_operands; n++)
    {
      if (xtensa_operand_is_register (isa, opcode, n) == 0
	  && xtensa_operand_is_PCrelative (isa, opcode, n) == 1)
	return TRUE;
    }
  return FALSE;
}
