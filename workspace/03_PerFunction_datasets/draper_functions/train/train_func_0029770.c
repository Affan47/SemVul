getfield(char *newline)
{
  static char *line = NULL;
  char  *end, *field;

  if (newline)
    line = newline;

  if (line == NULL)
    return(NULL);

  field = line;
  if ((end = strchr(line,':')) == NULL)
    {
      line = NULL;
      if ((end = strchr(field,'\n')) == NULL)
        end = field + strlen(field);
    }
  else
    line = end + 1;
  *end = '\0';
  return(field);
}
