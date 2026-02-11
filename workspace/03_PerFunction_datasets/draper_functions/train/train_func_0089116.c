reset_used_flags (x)
     rtx x;
{
  int i, j;
  enum rtx_code code;
  const char *format_ptr;
  int length;


repeat:
  if (x == 0)
    return;

  code = GET_CODE (x);


  switch (code)
    {
    case REG:
    case QUEUED:
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case SYMBOL_REF:
    case CODE_LABEL:
    case PC:
    case CC0:
      return;

    case INSN:
    case JUMP_INSN:
    case CALL_INSN:
    case NOTE:
    case LABEL_REF:
    case BARRIER:

      return;

    default:
      break;
    }

  RTX_FLAG (x, used) = 0;

  format_ptr = GET_RTX_FORMAT (code);
  length = GET_RTX_LENGTH (code);

  for (i = 0; i < length; i++)
    {
      switch (*format_ptr++)
	{
	case 'e':
          if (i == length-1)
            {
              x = XEXP (x, i);
	      goto repeat;
            }
	  reset_used_flags (XEXP (x, i));
	  break;

	case 'E':
	  for (j = 0; j < XVECLEN (x, i); j++)
	    reset_used_flags (XVECEXP (x, i, j));
	  break;
	}
    }
}
