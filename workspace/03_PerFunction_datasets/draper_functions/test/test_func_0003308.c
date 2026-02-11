record_hard_reg_sets (rtx x, const_rtx pat ATTRIBUTE_UNUSED, void *data)
{
  HARD_REG_SET *pset = (HARD_REG_SET *)data;
  if (REG_P (x) && REGNO (x) < FIRST_PSEUDO_REGISTER)
    {
      int nregs = hard_regno_nregs[REGNO (x)][GET_MODE (x)];
      while (nregs-- > 0)
	SET_HARD_REG_BIT (*pset, REGNO (x) + nregs);
    }
}
