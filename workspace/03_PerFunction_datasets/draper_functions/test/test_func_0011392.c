search (const char *netname, char *result, int *errnop, int secret)
{
  FILE *stream = fopen (DATAFILE, "rce");
  if (stream == NULL)
    return errno == EAGAIN ? NSS_STATUS_TRYAGAIN : NSS_STATUS_UNAVAIL;

  for (;;)
    {
      char buffer[HEXKEYBYTES * 2 + KEYCHECKSUMSIZE + MAXNETNAMELEN + 17];
      char *p;
      char *save_ptr;

      buffer[sizeof (buffer) - 1] = '\xff';
      p = fgets_unlocked (buffer, sizeof (buffer), stream);
      if (p == NULL)
	{

	  *errnop = errno;
	  fclose (stream);
	  return NSS_STATUS_NOTFOUND;
	}
      else if (buffer[sizeof (buffer) - 1] != '\xff')
	{

	  if (buffer[sizeof (buffer) - 2] != '\0')
	    while (getc_unlocked (stream) != '\n')
	      continue;
	  continue;
	}


      p = __strtok_r (buffer, "# \t:\n", &save_ptr);
      if (p == NULL)
	continue;
      if (strcmp (p, netname) != 0)
	continue;


      p = __strtok_r (NULL, ":\n", &save_ptr);
      if (p == NULL)
	continue;
      if (secret)
	p = __strtok_r (NULL, ":\n", &save_ptr);
      if (p == NULL)
	continue;
      fclose (stream);
      strcpy (result, p);
      return NSS_STATUS_SUCCESS;
    }
}
