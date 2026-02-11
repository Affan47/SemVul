find_used_regs (xptr, data)
     rtx *xptr;
     void *data ATTRIBUTE_UNUSED;
{
  int i, j;
  enum rtx_code code;
  const char *fmt;
  rtx x = *xptr;


 repeat:
  if (x == 0)
    return;

  code = GET_CODE (x);
  if (REG_P (x))
    {
      if (reg_use_count == MAX_USES)
	return;

      reg_use_table[reg_use_count].reg_rtx = x;
      reg_use_count++;
    }


  for (i = GET_RTX_LENGTH (code) - 1, fmt = GET_RTX_FORMAT (code); i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{


	  if (i == 0)
	    {
	      x = XEXP (x, 0);
	      goto repeat;
	    }

	  find_used_regs (&XEXP (x, i), data);
	}
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  find_used_regs (&XVECEXP (x, i, j), data);
    }
}
