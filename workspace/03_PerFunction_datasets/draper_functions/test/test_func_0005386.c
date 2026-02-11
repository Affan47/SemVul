get_parameter(char *string)
{
  char *pnt;

  while (*string == ' ' || *string == '\t' || *string == '=')
    ++string;

  pnt = string;
  while (*pnt != '\n' && *pnt != '#' && *pnt != '\0')
    ++pnt;
  *pnt = '\0';

  return string;
}
