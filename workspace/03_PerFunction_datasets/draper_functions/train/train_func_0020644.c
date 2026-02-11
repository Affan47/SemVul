strtoupper(char *str)
{
  char *p, *q;

  p = strdup(str);
  for (q = p; *q != '\0'; q++) {
	if (islower((int) *q))
	  *q = toupper((int) *q);
  }

  return(p);
}
