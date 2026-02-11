xt_true_regnum (rtx x)
{
  if (GET_CODE (x) == REG)
    {
      if (reg_renumber
	  && REGNO (x) >= FIRST_PSEUDO_REGISTER
	  && reg_renumber[REGNO (x)] >= 0)
	return reg_renumber[REGNO (x)];
      return REGNO (x);
    }
  if (GET_CODE (x) == SUBREG)
    {
      int base = xt_true_regnum (SUBREG_REG (x));
      if (base >= 0 && base < FIRST_PSEUDO_REGISTER)
        return base + subreg_regno_offset (REGNO (SUBREG_REG (x)),
                                           GET_MODE (SUBREG_REG (x)),
                                           SUBREG_BYTE (x), GET_MODE (x));
    }
  return -1;
}
