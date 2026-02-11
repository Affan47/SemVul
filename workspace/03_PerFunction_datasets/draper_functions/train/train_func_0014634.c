free_bb_for_insn ()
{
  rtx insn;
  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    if (GET_CODE (insn) != BARRIER)
      BLOCK_FOR_INSN (insn) = NULL;
}
