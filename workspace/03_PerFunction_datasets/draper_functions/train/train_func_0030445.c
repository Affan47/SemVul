slots_overlap_p (rtx s1, rtx s2)
{
  rtx base1, base2;
  HOST_WIDE_INT ofs1 = 0, ofs2 = 0;
  int size1 = GET_MODE_SIZE (GET_MODE (s1));
  int size2 = GET_MODE_SIZE (GET_MODE (s2));
  if (GET_CODE (s1) == SUBREG)
    ofs1 = SUBREG_BYTE (s1), s1 = SUBREG_REG (s1);
  if (GET_CODE (s2) == SUBREG)
    ofs2 = SUBREG_BYTE (s2), s2 = SUBREG_REG (s2);

  if (s1 == s2)
    return 1;

  if (GET_CODE (s1) != GET_CODE (s2))
    return 0;

  if (GET_CODE (s1) == REG && GET_CODE (s2) == REG)
    {
      if (REGNO (s1) != REGNO (s2))
	return 0;
      if (ofs1 >= ofs2 + size2 || ofs2 >= ofs1 + size1)
	return 0;
      return 1;
    }
  if (GET_CODE (s1) != MEM || GET_CODE (s2) != MEM)
    abort ();
  s1 = XEXP (s1, 0);
  s2 = XEXP (s2, 0);
  if (GET_CODE (s1) != PLUS || GET_CODE (XEXP (s1, 0)) != REG
      || GET_CODE (XEXP (s1, 1)) != CONST_INT)
    return 1;
  if (GET_CODE (s2) != PLUS || GET_CODE (XEXP (s2, 0)) != REG
      || GET_CODE (XEXP (s2, 1)) != CONST_INT)
    return 1;
  base1 = XEXP (s1, 0);
  base2 = XEXP (s2, 0);
  if (!rtx_equal_p (base1, base2))
    return 1;
  ofs1 += INTVAL (XEXP (s1, 1));
  ofs2 += INTVAL (XEXP (s2, 1));
  if (ofs1 >= ofs2 + size2 || ofs2 >= ofs1 + size1)
    return 0;
  return 1;
}
