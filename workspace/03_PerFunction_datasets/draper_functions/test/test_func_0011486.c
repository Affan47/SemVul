escape_string_for_mysql(CHARSET_INFO *charset_info,
                               char *to, size_t to_length,
                               const char *from, size_t length)
{
  const char *to_start= to;
  const char *end, *to_end=to_start + (to_length ? to_length-1 : 2*length);
  my_bool overflow= FALSE;
#ifdef USE_MB
  my_bool use_mb_flag= use_mb(charset_info);
#endif
  for (end= from + length; from < end; from++)
  {
    char escape= 0;
#ifdef USE_MB
    int tmp_length;
    if (use_mb_flag && (tmp_length= my_ismbchar(charset_info, from, end)))
    {
      if (to + tmp_length > to_end)
      {
        overflow= TRUE;
        break;
      }
      while (tmp_length--)
	*to++= *from++;
      from--;
      continue;
    }


    if (use_mb_flag && (tmp_length= my_mbcharlen(charset_info, *from)) > 1)
      escape= *from;
    else
#endif
    switch (*from) {
    case 0:
      escape= '0';
      break;
    case '\n':
      escape= 'n';
      break;
    case '\r':
      escape= 'r';
      break;
    case '\\':
      escape= '\\';
      break;
    case '\'':
      escape= '\'';
      break;
    case '"':
      escape= '"';
      break;
    case '\032':
      escape= 'Z';
      break;
    }
    if (escape)
    {
      if (to + 2 > to_end)
      {
        overflow= TRUE;
        break;
      }
      *to++= '\\';
      *to++= escape;
    }
    else
    {
      if (to + 1 > to_end)
      {
        overflow= TRUE;
        break;
      }
      *to++= *from;
    }
  }
  *to= 0;
  return overflow ? (size_t) -1 : (size_t) (to - to_start);
}
