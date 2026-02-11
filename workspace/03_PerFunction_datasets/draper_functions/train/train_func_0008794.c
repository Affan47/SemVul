get_name (struct in_addr *host, int type)
{
  char *buf;
  int i;
  struct hostent *hp;
#ifdef h_addr
  char **pp;
#endif

  hp = gethostbyaddr ((char *) host, sizeof (*host), type);
  if (hp == NULL)
    {
      return NULL;
    }
  i = strlen (hp->h_name);
  buf = (char *) xmalloc (i + 1);
  strcpy (buf, hp->h_name);
  hp = gethostbyname (buf);
  if (hp == NULL)
    return NULL;


#ifdef h_addr
  for (pp = hp->h_addr_list; *pp; pp++)
    {
      if (memcmp ((char *) &host->s_addr, (char *) *pp, hp->h_length) == 0)
	{
	  break;
	}
    }
  if (*pp == NULL)
    {
      return NULL;
    }
#else
  if (memcmp ((char *) &host->s_addr, (char *) hp->h_addr, hp->h_length) != 0)
    {
      return NULL;
    }
#endif

  return buf;
}
