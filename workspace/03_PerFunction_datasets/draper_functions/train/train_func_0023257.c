is_correct_date_format (format_txt, use_day_suffix, use_short3_day_name,
			use_day_zeroleaded, use_year_zeroleaded)
     char *format_txt;
     Bool *use_day_suffix;
     Bool *use_short3_day_name;
     Bool *use_day_zeroleaded;
     Bool *use_year_zeroleaded;


{
  register int start_highlighting = 2;
  register int end_highlighting = 2;
  register int weekday_name_group = 2;
  register int day_group = 2;
  register int month_group = 2;
  register int year_group = 2;
  register int pos;
  auto int fstyle = FSTYLE_NONE;
  auto int fwidth = SPECIAL_VALUE;
  auto Bool is_cformat = FALSE;
  auto Bool is_lformat = FALSE;
  auto Bool is_sign = FALSE;
  auto Bool is_lzero = FALSE;
  auto Bool is_fformat = FALSE;
  auto Bool is_suffix = FALSE;


  *use_day_suffix = (*use_short3_day_name) = (*use_day_zeroleaded) =
    (*use_year_zeroleaded) = FALSE;
  if (!*format_txt)


    return (FALSE);
  do
    {
      while (*format_txt
	     && (*format_txt != DFORMAT_CHAR) && (*format_txt != QUOTE_CHAR))
	format_txt++;
      if (*format_txt)
	{
	  if (*format_txt == DFORMAT_CHAR)
	    {
	      pos = decode_format (format_txt, 1, &is_cformat,
				   &is_lformat, &is_sign, &is_lzero,
				   &is_suffix, &is_fformat, &fstyle, &fwidth);
	      format_txt += pos;


	      switch (*format_txt)
		{
		case HLS1S_CHAR:
		  if (end_highlighting == 2)
		    if (start_highlighting)
		      start_highlighting--;
		  break;
		case HLS1E_CHAR:
		  if (start_highlighting == 1)
		    if (end_highlighting)
		      end_highlighting--;
		  break;
		case DAYNR_CHAR:
		  if (is_lzero)
		    *use_day_zeroleaded = TRUE;
		  if (is_suffix)
		    *use_day_suffix = TRUE;
		  if (day_group)
		    day_group--;
		  break;
		case WDNAME_CHAR:
		  if (fwidth == 3)
		    *use_short3_day_name = TRUE;
		  if (weekday_name_group)
		    weekday_name_group--;
		  break;
		case MONTHNAME_CHAR:
		case MONTHNR_CHAR:
		  if (month_group)
		    month_group--;
		  break;
		case YEARNR_CHAR:
		  if (is_lzero)
		    *use_year_zeroleaded = TRUE;
		  if (year_group)
		    year_group--;
		  break;
		default:


		  return (FALSE);
		}
	    }
	  else


	  if (!*++format_txt)
	    format_txt--;
	  format_txt++;
	}
      else
	break;
    }
  while (*format_txt);
  if (start_highlighting != 1
      || end_highlighting != 1
      || day_group != 1 || month_group != 1 || year_group != 1)


    return (FALSE);
  if (weekday_name_group < 1)


    return (FALSE);

  return (TRUE);
}
