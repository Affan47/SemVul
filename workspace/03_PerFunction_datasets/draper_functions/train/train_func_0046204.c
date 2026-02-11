copy_token ( char **dest, char *source)
{
  char *endpos, savepos;

  endpos = source;
  while (*endpos != ' ' && *endpos != '\t' && *endpos != '\0')
    endpos++;
  if (*endpos == '\0')
    {
      *dest = NULL;
      return (NULL);
    }

  savepos = *endpos;
  *endpos = '\0';
  *dest = g_malloc0 ((gulong) (endpos - source + 1));
  strcpy (*dest, source);
  *endpos = savepos;


  source = endpos + 1;
  while ((*source == ' ' || *source == '\t') && *source != '\0')
    source++;
  return (source);
}
