findPrCategory (IndexFileDesc fp, const char *number)
{
  char *buf;
  char *res = NULL;

  while ((res == NULL) && (buf = read_line (fp->fileDes, NULL)) != NULL)
    {
      if (buf[0] != '#')
	{
	  char *start = buf;
	  char *end = strchr (start, '/');
	  if (end != NULL)
	    {
	      char *numStart = end + 1;
	      char *category = start;

	      *end = '\0';
	      end = find_sep (fp->desc, numStart);
	      if (end != NULL)
		{
		  *end = '\0';

		  if (strcmp (numStart, number) == 0)
		    {
		      res = xstrdup (category);
		    }
		}
	    }
	}
      free (buf);
    }

  return res;
}
