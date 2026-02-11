str_to_offset(const char *str, uint length, long *offset)
{
  const char *end= str + length;
  my_bool negative;
  ulong number_tmp;
  long offset_tmp;

  if (length < 4)
    return 1;

  if (*str == '+')
    negative= 0;
  else if (*str == '-')
    negative= 1;
  else
    return 1;
  str++;

  number_tmp= 0;

  while (str < end && my_isdigit(&my_charset_latin1, *str))
  {
    number_tmp= number_tmp*10 + *str - '0';
    str++;
  }

  if (str + 1 >= end || *str != ':')
    return 1;
  str++;

  offset_tmp = number_tmp * MINS_PER_HOUR; number_tmp= 0;

  while (str < end && my_isdigit(&my_charset_latin1, *str))
  {
    number_tmp= number_tmp * 10 + *str - '0';
    str++;
  }

  if (str != end)
    return 1;

  offset_tmp= (offset_tmp + number_tmp) * SECS_PER_MIN;

  if (negative)
    offset_tmp= -offset_tmp;


  if (number_tmp > 59 || offset_tmp < -13 * SECS_PER_HOUR + 1 ||
      offset_tmp > 13 * SECS_PER_HOUR)
    return 1;

  *offset= offset_tmp;

  return 0;
}
