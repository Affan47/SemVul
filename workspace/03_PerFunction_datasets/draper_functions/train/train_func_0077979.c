get_relocation_opnd (xtensa_opcode opcode, int r_type)
{
  xtensa_isa isa = xtensa_default_isa;
  int last_immed, last_opnd, opi;

  if (opcode == XTENSA_UNDEFINED)
    return XTENSA_UNDEFINED;


  last_immed = XTENSA_UNDEFINED;
  last_opnd = xtensa_opcode_num_operands (isa, opcode);
  for (opi = last_opnd - 1; opi >= 0; opi--)
    {
      if (xtensa_operand_is_visible (isa, opcode, opi) == 0)
	continue;
      if (xtensa_operand_is_PCrelative (isa, opcode, opi) == 1)
	{
	  last_immed = opi;
	  break;
	}
      if (last_immed == XTENSA_UNDEFINED
	  && xtensa_operand_is_register (isa, opcode, opi) == 0)
	last_immed = opi;
    }
  if (last_immed < 0)
    return XTENSA_UNDEFINED;


  if (r_type >= R_XTENSA_OP0 && r_type <= R_XTENSA_OP2)
    {
      int reloc_opnd = r_type - R_XTENSA_OP0;
      if (reloc_opnd != last_immed)
	return XTENSA_UNDEFINED;
    }

  return last_immed;
}
