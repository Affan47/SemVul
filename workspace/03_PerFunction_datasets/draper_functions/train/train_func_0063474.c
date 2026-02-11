replacement_quality (rtx reg)
{
  int src_regno;


  if (GET_CODE (reg) != REG)
    return 0;


  if (REG_LIVE_LENGTH (REGNO (reg)) < 0)
    return 0;

  src_regno = regno_src_regno[REGNO (reg)];


  if (src_regno < 0)
    return 3;


  if (src_regno < FIRST_PSEUDO_REGISTER)
    return 1;


  return 2;
}
