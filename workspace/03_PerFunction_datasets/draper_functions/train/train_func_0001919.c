if_flagtoname (int flag, const char *avoid)
{
  struct if_flag *fp;
  const char *first_match = NULL;
  char *start;

  for (fp = if_flags; ; fp++)
    {
      if (!fp->name)
	return NULL;
      if (flag == fp->mask && !fp->rev)
	break;
    }

  first_match = fp->name;


  if (avoid)
    do
      {
	start = strstr (avoid, fp->name);
	if (!start || *(start - 1) != ':'
	    || *(start + strlen (fp->name)) != ':')
	  break;
	fp++;
      }
    while (fp->name);

  if (fp->name)
    return fp->name;
  else
    return first_match;
}
