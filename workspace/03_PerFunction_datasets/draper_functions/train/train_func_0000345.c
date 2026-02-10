find_a_file (struct path_prefix *pprefix, const char *name, int mode)
{
  char *temp;
  struct prefix_list *pl;
  int len = pprefix->max_len + strlen (name) + 1;

  if (debug)
    fprintf (stderr, "Looking for '%s'\n", name);

#ifdef HOST_EXECUTABLE_SUFFIX
  len += strlen (HOST_EXECUTABLE_SUFFIX);
#endif

  temp = XNEWVEC (char, len);


  if (IS_ABSOLUTE_PATH (name))
    {
      if (access (name, mode) == 0)
	{
	  strcpy (temp, name);

	  if (debug)
	    fprintf (stderr, "  - found: absolute path\n");

	  return temp;
	}

#ifdef HOST_EXECUTABLE_SUFFIX


      strcpy (temp, name);
	strcat (temp, HOST_EXECUTABLE_SUFFIX);

	if (access (temp, mode) == 0)
	  return temp;
#endif

      if (debug)
	fprintf (stderr, "  - failed to locate using absolute path\n");
    }
  else
    for (pl = pprefix->plist; pl; pl = pl->next)
      {
	struct stat st;

	strcpy (temp, pl->prefix);
	strcat (temp, name);

	if (stat (temp, &st) >= 0
	    && ! S_ISDIR (st.st_mode)
	    && access (temp, mode) == 0)
	  return temp;

#ifdef HOST_EXECUTABLE_SUFFIX


	strcat (temp, HOST_EXECUTABLE_SUFFIX);

	if (stat (temp, &st) >= 0
	    && ! S_ISDIR (st.st_mode)
	    && access (temp, mode) == 0)
	  return temp;
#endif
      }

  if (debug && pprefix->plist == NULL)
    fprintf (stderr, "  - failed: no entries in prefix list\n");

  free (temp);
  return 0;
}
