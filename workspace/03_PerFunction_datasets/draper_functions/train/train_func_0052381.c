strip_beginning_spaces(char *str)
{
  char *pc = str;
  int diff = 0;


  while (*pc == ' ')
    pc++;
  diff = pc - str;


  while (*pc != '\0')
    {
      *(pc - diff) = *pc;
      pc++;
    }
  *(pc - diff) = '\0';
}
