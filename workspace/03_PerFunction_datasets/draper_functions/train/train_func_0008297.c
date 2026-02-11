prefix_from_string (const char *p, struct path_prefix *pprefix)
{
  const char *startp, *endp;
  char *nstore = xmalloc (strlen (p) + 3);

  if (debug)
    fprintf (stderr, "Convert string '%s' into prefixes, separator = '%c'\n", p, PATH_SEPARATOR);

  startp = endp = p;
  while (1)
    {
      if (*endp == PATH_SEPARATOR || *endp == 0)
	{
	  strncpy (nstore, startp, endp-startp);
	  if (endp == startp)
	    {
	      strcpy (nstore, "./");
	    }
	  else if (! IS_DIR_SEPARATOR (endp[-1]))
	    {
	      nstore[endp-startp] = DIR_SEPARATOR;
	      nstore[endp-startp+1] = 0;
	    }
	  else
	    nstore[endp-startp] = 0;

	  if (debug)
	    fprintf (stderr, "  - add prefix: %s\n", nstore);

	  add_prefix (pprefix, nstore);
	  if (*endp == 0)
	    break;
	  endp = startp = endp + 1;
	}
      else
	endp++;
    }
}
