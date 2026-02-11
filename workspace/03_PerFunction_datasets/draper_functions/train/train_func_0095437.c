attr_rtx_cost (x)
     rtx x;
{
  int cost = 0;
  enum rtx_code code;
  if (!x)
    return 0;
  code = GET_CODE (x);
  switch (code)
    {
    case MATCH_OPERAND:
      if (XSTR (x, 1)[0])
	return 10;
      else
	return 0;
    case EQ_ATTR:

      if (!strcmp (XSTR (x, 0), "alternative"))
	return 0;
      else
	return 5;
    default:
      {
	int i, j;
	const char *fmt = GET_RTX_FORMAT (code);
	for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
	  {
	    switch (fmt[i])
	      {
	      case 'V':
	      case 'E':
		for (j = 0; j < XVECLEN (x, i); j++)
		  cost += attr_rtx_cost (XVECEXP (x, i, j));
		break;
	      case 'e':
		cost += attr_rtx_cost (XEXP (x, i));
		break;
	      }
	  }
      }
      break;
    }
  return cost;
}
