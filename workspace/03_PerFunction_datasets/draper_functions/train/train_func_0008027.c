reg_subword_p (rtx x, rtx reg)
{

  if (!REG_P (reg) || GET_MODE_CLASS (GET_MODE (reg)) != MODE_INT)
    return false;

  if (GET_CODE (x) == STRICT_LOW_PART
      || GET_CODE (x) == ZERO_EXTRACT)
    x = XEXP (x, 0);

  return GET_CODE (x) == SUBREG
	 && SUBREG_REG (x) == reg
	 && GET_MODE_CLASS (GET_MODE (x)) == MODE_INT;
}
