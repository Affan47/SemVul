first_active_insn (basic_block bb)
{
  rtx insn = BB_HEAD (bb);

  if (LABEL_P (insn))
    {
      if (insn == BB_END (bb))
	return NULL_RTX;
      insn = NEXT_INSN (insn);
    }

  while (NOTE_P (insn) || DEBUG_INSN_P (insn))
    {
      if (insn == BB_END (bb))
	return NULL_RTX;
      insn = NEXT_INSN (insn);
    }

  if (JUMP_P (insn))
    return NULL_RTX;

  return insn;
}
