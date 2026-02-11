ft_boolean_check_syntax_string(const uchar *str)
{
  uint i, j;

  if (!str ||
      (strlen((char*) str)+1 != sizeof(DEFAULT_FTB_SYNTAX)) ||
      (str[0] != ' ' && str[1] != ' '))
    return 1;
  for (i=0; i<sizeof(DEFAULT_FTB_SYNTAX); i++)
  {

    if ((unsigned char)(str[i]) > 127 || my_isalnum(default_charset_info, str[i]))
      return 1;
    for (j=0; j<i; j++)
      if (str[i] == str[j] && (i != 11 || j != 10))
        return 1;
  }
  return 0;
}
