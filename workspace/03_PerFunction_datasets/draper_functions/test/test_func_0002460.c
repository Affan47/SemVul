host2netname (char netname[MAXNETNAMELEN + 1], const char *host,
	      const char *domain)
{
  char *p;
  char hostname[MAXHOSTNAMELEN + 1];
  char domainname[MAXHOSTNAMELEN + 1];
  char *dot_in_host;
  size_t i;

  netname[0] = '\0';

  if (host == NULL)
    __gethostname (hostname, MAXHOSTNAMELEN);
  else
    {
      strncpy (hostname, host, MAXHOSTNAMELEN);
      hostname[MAXHOSTNAMELEN] = '\0';
    }

  dot_in_host = strchr (hostname, '.');
  if (domain == NULL)
    {
      p = dot_in_host;
      if (p)
	{
	  ++p;
	  strncpy (domainname, p, MAXHOSTNAMELEN);
	  domainname[MAXHOSTNAMELEN] = '\0';
	}
      else
	{
	  domainname[0] = 0;
	  getdomainname (domainname, MAXHOSTNAMELEN);
	}
    }
  else
    {
      strncpy (domainname, domain, MAXHOSTNAMELEN);
      domainname[MAXHOSTNAMELEN] = '\0';
    }

  i = strlen (domainname);
  if (i == 0)

    return 0;
  if (domainname[i - 1] == '.')
    domainname[i - 1] = 0;

  if (dot_in_host)
    *dot_in_host = '\0';

  if ((strlen (domainname) + strlen (hostname) + OPSYS_LEN + 3)
      > MAXNETNAMELEN)
    return 0;

  sprintf (netname, "%s.%s@%s", OPSYS, hostname, domainname);
  return 1;
}
