next_frag_opcode_is_loop (const fragS *fragP, xtensa_opcode *opcode)
{
  xtensa_opcode out_opcode;
  const fragS *next_fragP = next_non_empty_frag (fragP);

  if (next_fragP == NULL)
    return FALSE;

  out_opcode = get_opcode_from_buf (next_fragP->fr_literal, 0);
  if (xtensa_opcode_is_loop (xtensa_default_isa, out_opcode) == 1)
    {
      *opcode = out_opcode;
      return TRUE;
    }
  return FALSE;
}
