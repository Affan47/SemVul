__argmatch_internal (const char *arg, const char *const *arglist,
		     const char *vallist, size_t valsize,
		     int case_sensitive)
{
  int i;
  size_t arglen;
  int matchind = -1;
  int ambiguous = 0;

  arglen = strlen (arg);


  for (i = 0; arglist[i]; i++)
    {
      if (case_sensitive
	  ? !strncmp (arglist[i], arg, arglen)
	  : !strncasecmp (arglist[i], arg, arglen))
	{
	  if (strlen (arglist[i]) == arglen)

	    return i;
	  else if (matchind == -1)

	    matchind = i;
	  else
	    {

	      if (vallist == NULL
		  || memcmp (vallist + valsize * matchind,
			     vallist + valsize * i, valsize))
		{


		  ambiguous = 1;
		}
	    }
	}
    }
  if (ambiguous)
    return -2;
  else
    return matchind;
}
