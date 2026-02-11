add_insn (rtx insn)
{
  PREV_INSN (insn) = get_last_insn();
  NEXT_INSN (insn) = 0;

  if (NULL != get_last_insn())
    NEXT_INSN (get_last_insn ()) = insn;

  if (NULL == get_insns ())
    set_first_insn (insn);

  set_last_insn (insn);
}
