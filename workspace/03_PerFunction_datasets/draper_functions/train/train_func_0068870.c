copy_insn_p (insn, source, target)
     rtx insn;
     rtx *source;
     rtx *target;
{
  rtx d, s;
  unsigned int d_regno, s_regno;
  int uid = INSN_UID (insn);

  if (!INSN_P (insn))
    abort ();


  if (copy_cache[uid].seen)
    {

      if (copy_cache[uid].seen == 1)
	{
	  if (source)
	    *source = copy_cache[uid].source;
	  if (target)
	    *target = copy_cache[uid].target;
	  return 1;
	}
      return 0;
    }


  copy_cache[uid].seen = 2;
  insn = single_set (insn);
  if (!insn)
    return 0;
  d = SET_DEST (insn);
  s = SET_SRC (insn);


  while (GET_CODE (d) == STRICT_LOW_PART)
    d = XEXP (d, 0);
  if (GET_CODE (d) != REG
      && (GET_CODE (d) != SUBREG || GET_CODE (SUBREG_REG (d)) != REG))
    return 0;
  while (GET_CODE (s) == STRICT_LOW_PART)
    s = XEXP (s, 0);
  if (GET_CODE (s) != REG
      && (GET_CODE (s) != SUBREG || GET_CODE (SUBREG_REG (s)) != REG))
    return 0;

  s_regno = (unsigned) REGNO (GET_CODE (s) == SUBREG ? SUBREG_REG (s) : s);
  d_regno = (unsigned) REGNO (GET_CODE (d) == SUBREG ? SUBREG_REG (d) : d);


  if ((s_regno < FIRST_PSEUDO_REGISTER
       && d_regno < FIRST_PSEUDO_REGISTER)
      || s_regno >= max_normal_pseudo
      || d_regno >= max_normal_pseudo)
    return 0;

  if (source)
    *source = s;
  if (target)
    *target = d;


  copy_cache[uid].seen = 1;
  copy_cache[uid].source = s;
  copy_cache[uid].target = d;
  return 1;
}
