note_add_store (rtx loc, const_rtx expr ATTRIBUTE_UNUSED, void *data)
{
  rtx insn;
  note_add_store_info *info = (note_add_store_info *) data;
  int r, n;

  if (!REG_P (loc))
    return;


  for (insn = info->first;
       insn != NEXT_INSN (info->current);
       insn = NEXT_INSN (insn))
    if (reg_referenced_p (loc, PATTERN (insn)))
      return;


  if (!info->fixed_regs_live)
    {
      info->failure =  true;
      return;
    }

  r = REGNO (loc);
  n = hard_regno_nregs[r][GET_MODE (loc)];
  while (--n >=  0)
    if (REGNO_REG_SET_P (info->fixed_regs_live, r+n))
      info->failure =  true;
}
