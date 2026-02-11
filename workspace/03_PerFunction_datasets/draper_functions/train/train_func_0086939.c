cvthname (struct sockaddr *f, socklen_t len)
{
  int err;
  char *p;

  err = getnameinfo (f, len, addrstr, sizeof (addrstr),
		     NULL, 0, NI_NUMERICHOST);
  if (err)
    {
      dbg_printf ("Malformed from address: %s.\n",
		  gai_strerror (err));
      return "???";
    }

  dbg_printf ("cvthname(%s)\n", addrstr);

  err = getnameinfo (f, len, addrname, sizeof (addrname),
		     NULL, 0, NI_NAMEREQD);
  if (err)
    {
      dbg_printf ("Host name for your address (%s) unknown.\n", addrstr);
      return addrstr;
    }

  p = strchr (addrname, '.');
  if (p != NULL)
    {
      if (strcasecmp (p + 1, LocalDomain) == 0)
	*p = '\0';
      else
	{
	  int count;

	  if (StripDomains)
	    {
	      count = 0;
	      while (StripDomains[count])
		{
		  if (strcasecmp (p + 1, StripDomains[count]) == 0)
		    {
		      *p = '\0';
		      return addrname;
		    }
		  count++;
		}
	    }
	  if (LocalHosts)
	    {
	      count = 0;
	      while (LocalHosts[count])
		{
		  if (strcasecmp (addrname, LocalHosts[count]) == 0)
		    {
		      *p = '\0';
		      return addrname;
		    }
		  count++;
		}
	    }
	}
    }
  return addrname;
}
