read_token(char *str, int max)
{
  int i;
  i = 0;

  while(isspace(next))
    GETNEXT;

  while( (isalnum(next) || (next=='_')) && (i<max))
    {
      str[i++] = next;
      GETNEXT;
    }

  if(i==max) buferr();

  str[i] = '\0';

  return TRUE;
}
