unrelaxed_frag_has_b_j (fragS *fragP)
{
  static xtensa_insnbuf insnbuf = NULL;
  xtensa_isa isa = xtensa_default_isa;
  int offset = 0;

  if (!fragP->tc_frag_data.is_insn)
    return FALSE;

  if (!insnbuf)
    insnbuf = xtensa_insnbuf_alloc (isa);


  while (offset < fragP->fr_fix)
    {
      xtensa_format fmt;
      int slot;

      xtensa_insnbuf_from_chars
	(isa, insnbuf, (unsigned char *) fragP->fr_literal + offset, 0);
      fmt = xtensa_format_decode (isa, insnbuf);
      if (fmt == XTENSA_UNDEFINED)
	return FALSE;

      for (slot = 0; slot < xtensa_format_num_slots (isa, fmt); slot++)
	{
	  xtensa_opcode opcode =
	    get_opcode_from_buf (fragP->fr_literal + offset, slot);
	  if (xtensa_opcode_is_branch (isa, opcode) == 1
	      || xtensa_opcode_is_jump (isa, opcode) == 1)
	    return TRUE;
	}
      offset += xtensa_format_length (isa, fmt);
    }
  return FALSE;
}
