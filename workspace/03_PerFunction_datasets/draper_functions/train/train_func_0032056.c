tokenize_line(char *line, char **pwords, int ncols_requested)
{
  int ncols_observed = 0;
  char *p;
  char prev_char = 0;
  for (p=line; ; p++)
  {

    if (prev_char == 0)
    {
      pwords[ncols_observed++] = p;
      if (ncols_observed == ncols_requested)
        break;
    }

    if (!*p)
      break;

    if (*p == '\t')
      *p = 0;

    prev_char = *p;
  }
  return ncols_observed;
}
