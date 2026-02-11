can_move_up (const_basic_block bb, const_rtx insn, int n_insns)
{
  while (insn != BB_HEAD (bb) && n_insns > 0)
    {
      insn = PREV_INSN (insn);


      if (INSN_P (insn))
	n_insns--;
    }
  return n_insns <= 0;
}
