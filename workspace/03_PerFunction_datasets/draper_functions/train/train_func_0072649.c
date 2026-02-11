get_one_parameter(char *string, unsigned char mode)
{
  char *pnt;

  while (*string == ' ' || *string == '\t' || *string == '=')
    ++string;

  pnt = string;
  while (*pnt != '\n' && *pnt != ' ' && *pnt != '\t' && *pnt != '\0' && (mode == HASH_IGNORE || *pnt != '#'))
    ++pnt;
  *pnt = '\0';

  return string;
}
