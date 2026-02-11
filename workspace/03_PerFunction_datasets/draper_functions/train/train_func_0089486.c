prev_instr_is_a_loop (bfd_byte *contents,
		      bfd_size_type content_length,
		      bfd_size_type offset)
{
  xtensa_opcode prev_opcode;

  if (offset < 3)
    return FALSE;
  prev_opcode = insn_decode_opcode (contents, content_length, offset-3, 0);
  return (xtensa_opcode_is_loop (xtensa_default_isa, prev_opcode) == 1);
}
