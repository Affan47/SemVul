maximal_insn_latency (rtx insn)
{
  int insn_code;

  if (insn == 0)
    insn_code = DFA__ADVANCE_CYCLE;


  else
    {
      insn_code = dfa_insn_code (insn);
      if (insn_code > DFA__ADVANCE_CYCLE)
        return 0;
    }
  return internal_maximal_insn_latency (insn_code, insn);
}
