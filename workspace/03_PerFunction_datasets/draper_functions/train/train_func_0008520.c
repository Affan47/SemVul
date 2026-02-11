printf_flag_info (struct printf_info *const pinfo, size_t n, int *argtypes)
{
  return_val_if_fail (pinfo != NULL, SNV_ERROR);

  if (!(pinfo->state & (SNV_STATE_BEGIN | SNV_STATE_FLAG)))
    {
      PRINTF_ERROR (pinfo, "invalid specifier");
      return -1;
    }

  pinfo->state = SNV_STATE_FLAG;

  while (pinfo->state & SNV_STATE_FLAG)
    {
      switch (*pinfo->format)
	{
	case '#':
	  pinfo->alt = TRUE;
	  pinfo->format++;
	  break;

	case '0':
	  if (!pinfo->left)
	    pinfo->pad = '0';
	  pinfo->format++;
	  break;

	case '-':
	  pinfo->pad = ' ';
	  pinfo->left = TRUE;
	  pinfo->format++;
	  break;

	case ' ':
	  pinfo->space = TRUE;
	  pinfo->format++;
	  break;

	case '+':
	  pinfo->showsign = TRUE;
	  pinfo->format++;
	  break;

	case '\'':
	  pinfo->group = TRUE;
	  pinfo->format++;
	  break;

	default:
	  pinfo->state = ~(SNV_STATE_BEGIN | SNV_STATE_FLAG);
	  break;
	}
    }

  pinfo->format--;


  return 0;
}
