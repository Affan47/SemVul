get_par(char *key, char *s, int *nl, const char *fn, FILE *fp)
{
  FUNCNAME("get_par");
  static char    parameter[2*LENGTH];
  int     i, ol = *nl;

  while (*s  &&  *s++ != ':');
  while (*s  &&  IS_BLANK_CHAR(*s))  s++;

  i = 0;
  while (*s  &&  *s != COMMENT  && *s != '\n')
  {
    if (*s == '\\'  &&  *(s+1) == '\n')
    {
      (*nl)++;
      if (fgets(s, LENGTH, fp) == nil)
      {
	ERROR("EOF reached while reading parameters of key %s\n", key);
	if (ol == *nl-1) ERROR("Skipping line %d of file %s\n", *nl, fn);
	else     ERROR("Skipping lines %d-%d of file %s\n", ol, *nl, fn);

	return(nil);
      }
    }
    else
    {
      if (i == 2*LENGTH-1)
      {
	ERROR("parameter has more than %d characters.\n", i);
	if (ol == *nl)  ERROR("Skipping line %d of file %s\n", *nl, fn);
	else    ERROR("Skipping lines %d-%d of file %s\n", ol, *nl, fn);

	return(nil);
      }
      if (IS_BLANK_CHAR(*s))
      {
	parameter[i++] = ' ';
	s++;
	while (*s  &&  IS_BLANK_CHAR(*s)) s++;
      }
      else
      {
	parameter[i++] = *s++;
      }
    }
  }

  do
  {
    parameter[i--] = '\0';
  } while (i  &&  IS_BLANK_CHAR(parameter[i]));

  if (i == 0  &&  IS_BLANK_CHAR(parameter[0]))
  {
    ERROR("no parameter of key %s.\n", key);
    if (ol == *nl) ERROR("Skipping line %d of file %s\n", *nl, fn);
    else   ERROR("Skipping lines %d-%d of file %s\n", ol, *nl, fn);

    return(nil);
  }

  return(parameter);
}
