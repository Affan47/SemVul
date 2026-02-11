strbasename(char *pathname, char *suffix)
{
  char *last, *p, *q, *s;
  size_t len;

  len = strlen(pathname);
  if (len == 0)
	return("");

  s = strdup(pathname);
  p = s + len - 1;


  while (p > s && *p == '/')
	*p-- = '\0';


  if (*p == '/')
	return("/");

  if ((last = rindex(s, (int) '/')) != NULL)
	*last++ = '\0';
  else
	last = s;


  if (suffix != NULL && !streq(last, suffix)
	  && (q = strsuffix(last, strlen(last), suffix)) != NULL)
	*q = '\0';

  return(last);
}
