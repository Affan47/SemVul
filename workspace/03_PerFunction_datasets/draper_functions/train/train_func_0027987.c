find_sep (IndexDesc indexDesc, char *start)
{
  char *end;
  int seplen = strlen (indexDesc->separator);

  do {
    end = strchr (start, indexDesc->separator[0]);
    if (end != NULL)
      {
	if (seplen == 1 || strncmp (start, indexDesc->separator, seplen) == 0)
	  {
	    return end;
	  }
	end++;
      }
  } while (end != NULL);

  return end;
}
