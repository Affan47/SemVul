pcrel_reloc_fits (xtensa_opcode opc,
		  int opnd,
		  bfd_vma self_address,
		  bfd_vma dest_address)
{
  xtensa_isa isa = xtensa_default_isa;
  uint32 valp = dest_address;
  if (xtensa_operand_do_reloc (isa, opc, opnd, &valp, self_address)
      || xtensa_operand_encode (isa, opc, opnd, &valp))
    return FALSE;
  return TRUE;
}
