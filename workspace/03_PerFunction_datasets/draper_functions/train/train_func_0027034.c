clear_log_links (void)
{
  rtx insn;

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    if (INSN_P (insn))
      free_INSN_LIST_list (&LOG_LINKS (insn));
}
