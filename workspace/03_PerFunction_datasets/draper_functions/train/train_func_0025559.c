scan_paradoxical_subregs (rtx x)
{
  int i;
  const char *fmt;
  enum rtx_code code = GET_CODE (x);

  switch (code)
    {
    case REG:
    case CONST_INT:
    case CONST:
    case SYMBOL_REF:
    case LABEL_REF:
    case CONST_DOUBLE:
    case CONST_FIXED:
    case CONST_VECTOR:
    case CC0:
    case PC:
    case USE:
    case CLOBBER:
      return;

    case SUBREG:
      if (REG_P (SUBREG_REG (x))
	  && (GET_MODE_SIZE (GET_MODE (x))
	      > reg_max_ref_width[REGNO (SUBREG_REG (x))]))
	{
	  reg_max_ref_width[REGNO (SUBREG_REG (x))]
	    = GET_MODE_SIZE (GET_MODE (x));
	  mark_home_live_1 (REGNO (SUBREG_REG (x)), GET_MODE (x));
	}
      return;

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	scan_paradoxical_subregs (XEXP (x, i));
      else if (fmt[i] == 'E')
	{
	  int j;
	  for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	    scan_paradoxical_subregs (XVECEXP (x, i, j));
	}
    }
}
