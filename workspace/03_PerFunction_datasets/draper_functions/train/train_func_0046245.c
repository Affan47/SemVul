concat_INSN_LIST (rtx copy, rtx old)
{
  rtx new_rtx = old;
  for (; copy ; copy = XEXP (copy, 1))
    {
      new_rtx = alloc_INSN_LIST (XEXP (copy, 0), new_rtx);
      PUT_REG_NOTE_KIND (new_rtx, REG_NOTE_KIND (copy));
    }
  return new_rtx;
}
