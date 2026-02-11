alloc_INSN_LIST (rtx val, rtx next)
{
  rtx r;

  if (unused_insn_list)
    {
      r = unused_insn_list;
      unused_insn_list = XEXP (r, 1);
      XEXP (r, 0) = val;
      XEXP (r, 1) = next;
      PUT_REG_NOTE_KIND (r, VOIDmode);
    }
  else
    r = gen_rtx_INSN_LIST (VOIDmode, val, next);

  return r;
}
