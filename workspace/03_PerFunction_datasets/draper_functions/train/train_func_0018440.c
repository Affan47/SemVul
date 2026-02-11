narrow_instruction (bfd_byte *contents,
		    bfd_size_type content_length,
		    bfd_size_type offset)
{
  xtensa_opcode opcode;
  bfd_size_type insn_len;
  xtensa_isa isa = xtensa_default_isa;
  xtensa_format fmt;
  xtensa_insnbuf o_insnbuf;

  static xtensa_insnbuf insnbuf = NULL;
  static xtensa_insnbuf slotbuf = NULL;

  if (insnbuf == NULL)
    {
      insnbuf = xtensa_insnbuf_alloc (isa);
      slotbuf = xtensa_insnbuf_alloc (isa);
    }

  BFD_ASSERT (offset < content_length);

  if (content_length < 2)
    return FALSE;


  xtensa_insnbuf_from_chars (isa, insnbuf, &contents[offset],
			     content_length - offset);
  fmt = xtensa_format_decode (isa, insnbuf);
  if (xtensa_format_num_slots (isa, fmt) != 1)
    return FALSE;

  if (xtensa_format_get_slot (isa, fmt, 0, insnbuf, slotbuf) != 0)
    return FALSE;

  opcode = xtensa_opcode_decode (isa, fmt, 0, slotbuf);
  if (opcode == XTENSA_UNDEFINED)
    return FALSE;
  insn_len = xtensa_format_length (isa, fmt);
  if (insn_len > content_length)
    return FALSE;

  o_insnbuf = can_narrow_instruction (slotbuf, fmt, opcode);
  if (o_insnbuf)
    {
      xtensa_insnbuf_to_chars (isa, o_insnbuf, contents + offset,
			       content_length - offset);
      return TRUE;
    }

  return FALSE;
}
