sindex(char c,char *string)
{
  register char
    *p;

  for (p=string; *p; p++)
    if (c == (*p))
      return(p-string);
  return(-1);
}
