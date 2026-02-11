hostIpAddr (Host host)
{
  int i ;
  char *p ;
  char **newIpAddrs = NULL;
  struct in_addr ipAddr, *returnAddr ;
  struct hostent *hostEnt ;

  ASSERT(host->params != NULL);


  if (host->nextIpLookup <= theTime())
    {

      if ( !inet_aton (host->params->ipName,&ipAddr) )
	{
	  if ((hostEnt = gethostbyname (host->params->ipName)) == NULL)
	    syslog (LOG_ERR, HOST_RESOLV_ERROR, host->params->peerName,
		    host->params->ipName, host_err_str ()) ;
	  else
	    {

	      for (i = 0 ; hostEnt->h_addr_list[i] ; i++)
		;
	      i++;

	      newIpAddrs =
		(char **) MALLOC ( (i * sizeof(char *)) +
				  ( (i - 1) * hostEnt->h_length) ) ;
	      ASSERT (newIpAddrs != NULL) ;


	      p = (char *)&newIpAddrs [ i ] ;
	      i = 0;
	      for (i = 0 ; hostEnt->h_addr_list[i] ; i++)
		{
		  newIpAddrs[i] = p;
		  memcpy (p, hostEnt->h_addr_list[i], hostEnt->h_length) ;
		  p += hostEnt->h_length ;
		}
	      newIpAddrs[i] = NULL ;
	    }
	}
      else
	{
	  newIpAddrs = (char **) MALLOC (2 * sizeof(char *) + sizeof(ipAddr)) ;
	  ASSERT (newIpAddrs != NULL) ;
	  p = (char *)&newIpAddrs [ 2 ];
	  newIpAddrs[0] = p;
	  memcpy (p, (char *)&ipAddr, sizeof(ipAddr)) ;
	  newIpAddrs[1] = NULL;
	}

      if (newIpAddrs)
	{
	  if (host->ipAddrs)
	    FREE (host->ipAddrs) ;
	  host->ipAddrs = newIpAddrs ;
	  host->nextIpAddr = host->ipAddrs ;
	  host->nextIpLookup = theTime () + dnsExpPeriod ;
	}
      else
	{

	  host->nextIpLookup = theTime () + dnsRetPeriod ;
	}
    }

  if (host->ipAddrs)
    {
      returnAddr = (struct in_addr *)(host->nextIpAddr[0]) ;
      if (*(++host->nextIpAddr) == NULL)
	host->nextIpAddr = host->ipAddrs ;
    }
  else
    returnAddr = NULL ;

  return returnAddr ;
}
