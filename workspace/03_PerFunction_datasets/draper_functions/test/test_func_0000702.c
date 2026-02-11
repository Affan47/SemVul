reload_reg_rtx_reaches_end_p (rtx reg, int reloadnum)
{
  unsigned int i;

  for (i = REGNO (reg); i < END_REGNO (reg); i++)
    if (!reload_reg_reaches_end_p (i, reloadnum))
      return false;
  return true;
}
