CPS_NormalizeLine(char *line)
{
  char *p, *q;
  int space = 1, first = 1;


  for (p = q = line; *p; p++) {
    if (isspace(*p)) {
      if (!space)
        *q++ = ' ';
      space = 1;
      continue;
    }


    if (first && strchr("!;#%", *p))
      break;

    *q++ = *p;
    space = first = 0;
  }


  if (q > line && q[-1] == ' ')
    q--;

  *q = '\0';
}
