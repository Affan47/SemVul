searchttl (char *str)
{
  char buf[strlen (str) + 1];
  char *cptr, *dptr;
  uint32_t time;
  int i;

  dptr = strstr (str, "ttl=");
  if (dptr == NULL)
    return DEFAULT_TTL;;

  dptr += 4;
  i = 0;
  while (dptr[i] != '\0' && dptr[i] != ':')
    i++;
  if (i == 0)
    return DEFAULT_TTL;

  strncpy (buf, dptr, i);
  buf[i] = '\0';
  time = 0;

  dptr = buf;
  cptr = strchr (dptr, 'd');
  if (cptr != NULL)
    {
      *cptr = '\0';
      cptr++;
      time += atoi (dptr) * 60 * 60 * 24;
      dptr = cptr;
    }

  cptr = strchr (dptr, 'h');
  if (cptr != NULL)
    {
      *cptr = '\0';
      cptr++;
      time += atoi (dptr) * 60 * 60;
      dptr = cptr;
    }

  cptr = strchr (dptr, 'm');
  if (cptr != NULL)
    {
      *cptr = '\0';
      cptr++;
      time += atoi (dptr) * 60;
      dptr = cptr;
    }

  cptr = strchr (dptr, 's');
  if (cptr != NULL)
    *cptr = '\0';

  time += atoi (dptr);

  return time;
}
