isOnlyNumeric(const char *str)
{
  if (str == NULL)
    return true;
  for (unsigned i = 0, len = strlen(str); i < len; i++)
  {
    if (!isdigit(str[i]) && str[i] != '\0' && str[i] != '+' && str[i] != '-')
      return false;
  }
  return true;
}
