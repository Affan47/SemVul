parse2dates(char *dat, char **s, time_t *from_d, time_t *to_d)
{
  (*s)++;
  while (isblank(**s)) (*s)++;
  if(isdigit(**s)) {
    if(!parseDate(s, from_d)) {
       warning (dat, "Invalid date '%s'", *s);
       return 0;
    }
    while (isblank(**s)) (*s)++;
  }
  if (**s == '-') {
    (*s)++;
    while (isblank(**s)) (*s)++;
    if(isdigit(**s)) {
      if(!parseDate(s, to_d)) {
         warning (dat, "Invalid date '%s'", *s);
         return 0;
      }
    }
    while (isblank(**s)) (*s)++;
  }
  if (**s != ']') {
    warning(dat, "Expected ']', got '%s'", *s);
    return 0;
  }
  else
    (*s)++;
  while (isblank(**s)) (*s)++;
  return 1;
}
