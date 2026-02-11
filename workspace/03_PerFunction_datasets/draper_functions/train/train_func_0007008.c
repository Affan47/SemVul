verify_reg_in_set (rtx op, HARD_REG_SET *pset)
{
  unsigned regno, nregs;
  bool all_live, all_dead;
  if (!REG_P (op))
    return false;

  regno = REGNO (op);
  nregs = hard_regno_nregs[regno][GET_MODE (op)];
  all_live = all_dead = true;
  while (nregs-- > 0)
    if (TEST_HARD_REG_BIT (*pset, regno + nregs))
      all_dead = false;
    else
      all_live = false;
  if (!all_dead && !all_live)
    {
      fail_current_block = true;
      return false;
    }
  return all_live;
}
