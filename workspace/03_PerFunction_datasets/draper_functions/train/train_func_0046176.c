true_regnum (const_rtx x)
{
  if (REG_P (x))
    {
      if (REGNO (x) >= FIRST_PSEUDO_REGISTER
	  && (lra_in_progress || reg_renumber[REGNO (x)] >= 0))
	return reg_renumber[REGNO (x)];
      return REGNO (x);
    }
  if (GET_CODE (x) == SUBREG)
    {
      int base = true_regnum (SUBREG_REG (x));
      if (base >= 0
	  && base < FIRST_PSEUDO_REGISTER)
	{
	  struct subreg_info info;

	  subreg_get_info (lra_in_progress
			   ? (unsigned) base : REGNO (SUBREG_REG (x)),
			   GET_MODE (SUBREG_REG (x)),
			   SUBREG_BYTE (x), GET_MODE (x), &info);

	  if (info.representable_p)
	    return base + info.offset;
	}
    }
  return -1;
}
