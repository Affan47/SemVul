record_hard_reg_uses_1 (rtx *px, void *data)
{
  rtx x = *px;
  HARD_REG_SET *pused = (HARD_REG_SET *)data;

  if (REG_P (x) && REGNO (x) < FIRST_PSEUDO_REGISTER)
    {
      int nregs = hard_regno_nregs[REGNO (x)][GET_MODE (x)];
      while (nregs-- > 0)
	SET_HARD_REG_BIT (*pused, REGNO (x) + nregs);
    }
  return 0;
}
