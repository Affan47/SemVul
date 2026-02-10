haifa_change_pattern (rtx insn, rtx new_pat)
{
  sched_change_pattern (insn, new_pat);


  INSN_COST (insn) = -1;

  INSN_TICK (insn) = INVALID_TICK;
}
