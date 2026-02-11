use_crosses_set_p (const_rtx x, int from_luid)
{
  const char *fmt;
  int i;
  enum rtx_code code = GET_CODE (x);

  if (code == REG)
    {
      unsigned int regno = REGNO (x);
      unsigned endreg = END_REGNO (x);

#ifdef PUSH_ROUNDING


      if (regno == STACK_POINTER_REGNUM && PUSH_ARGS)
	return 1;
#endif
      for (; regno < endreg; regno++)
	{
	  reg_stat_type *rsp = VEC_index (reg_stat_type, reg_stat, regno);
	  if (rsp->last_set
	      && rsp->last_set_label == label_tick
	      && DF_INSN_LUID (rsp->last_set) > from_luid)
	    return 1;
	}
      return 0;
    }

  if (code == MEM && mem_last_set > from_luid)
    return 1;

  fmt = GET_RTX_FORMAT (code);

  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'E')
	{
	  int j;
	  for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	    if (use_crosses_set_p (XVECEXP (x, i, j), from_luid))
	      return 1;
	}
      else if (fmt[i] == 'e'
	       && use_crosses_set_p (XEXP (x, i), from_luid))
	return 1;
    }
  return 0;
}
