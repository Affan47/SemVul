next_nonnote_nondebug_insn (rtx insn)
{
  while (insn)
    {
      insn = NEXT_INSN (insn);
      if (insn == 0 || (!NOTE_P (insn) && !DEBUG_INSN_P (insn)))
	break;
    }

  return insn;
}
