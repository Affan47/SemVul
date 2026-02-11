enlist(cpp, new, len)
     char **cpp;
     char *new;
     int len;
{
  int i, j;

  if (cpp == NULL)
    return NULL;
  if ((new = icpyalloc(new)) == NULL)
    {
      freelist(cpp);
      return NULL;
    }
  new[len] = '\0';

  for (i = 0; cpp[i] != NULL; ++i)
    if (istrstr(cpp[i], new) != NULL)
      {
	free(new);
	return cpp;
      }

  j = 0;
  while (cpp[j] != NULL)
    if (istrstr(new, cpp[j]) == NULL)
      ++j;
    else
      {
	free(cpp[j]);
	if (--i == j)
	  break;
	cpp[j] = cpp[i];
	cpp[i] = NULL;
      }

  cpp = (char **) realloc((char *) cpp, (i + 2) * sizeof *cpp);
  if (cpp == NULL)
    return NULL;
  cpp[i] = new;
  cpp[i + 1] = NULL;
  return cpp;
}
