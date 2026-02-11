crunch_list (char **oldlist, char *list)
{
  int count, i;
  char *p, *q;

  p = list;


  while (p[strlen (p) - 1] == LIST_DELIMITER)
    {
      p[strlen (p) - 1] = '\0';
    }

  while (p[0] == LIST_DELIMITER)
    {
      p++;
    }


  if (*p == '\0')
    return oldlist;


  for (count = 1, i = 0; p[i]; i++)
    if (p[i] == LIST_DELIMITER)
      count++;


  for (i = 0; oldlist && oldlist[i]; i++)
    ;


  oldlist = (char **) realloc (oldlist, (i + count + 1) * sizeof (*oldlist));
  if (oldlist == NULL)
    error (EXIT_FAILURE, errno, "can't allocate memory");


  for (count = i; (q = strchr (p, LIST_DELIMITER)) != NULL;
       count++, p = q, p++)
    {
      oldlist[count] = (char *) malloc ((q - p + 1) * sizeof (char));
      if (oldlist[count] == NULL)
        error (EXIT_FAILURE, errno, "can't allocate memory");

      strncpy (oldlist[count], p, q - p);
      oldlist[count][q - p] = '\0';
    }


  oldlist[count] = (char *) xmalloc ((strlen (p) + 1) * sizeof (char));
  if (oldlist[count] == NULL)
    error (EXIT_FAILURE, errno, "can't allocate memory");

  strcpy (oldlist[count], p);

  oldlist[++count] = NULL;

  if (Debug)
    {
      for (count = 0; oldlist[count]; count++)
	printf ("#%d: %s\n", count, oldlist[count]);
    }
  return oldlist;
}
