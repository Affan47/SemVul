isOnlyAlphaNumeric(const char *str)
{
  unsigned int ui;
  unsigned int len;
  if (str == NULL)
    return true;
  for (ui = 0, len = sizeof(str); ui < len; ui++)
  {
    if (!isalpha(str[ui]) && !isdigit(str[ui]) && str[ui] != '\0')
      return false;
  }
  return true;
}
