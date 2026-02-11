addhstbyX (struct database_dyn *db, int fd, request_header *req,
	   void *key, uid_t uid, struct hashentry *he, struct datahead *dh)
{


  int buflen = 1024;
  char *buffer = (char *) alloca (buflen);
  struct hostent resultbuf;
  struct hostent *hst;
  bool use_malloc = false;
  int errval = 0;
  int32_t ttl = INT32_MAX;

  if (__builtin_expect (debug_level > 0, 0))
    {
      const char *str;
      char buf[INET6_ADDRSTRLEN + 1];
      if (req->type == GETHOSTBYNAME || req->type == GETHOSTBYNAMEv6)
	str = key;
      else
	str = inet_ntop (req->type == GETHOSTBYADDR ? AF_INET : AF_INET6,
			 key, buf, sizeof (buf));

      if (he == NULL)
	dbg_log (_("Haven't found \"%s\" in hosts cache!"), (char *) str);
      else
	dbg_log (_("Reloading \"%s\" in hosts cache!"), (char *) str);
    }

  while (lookup (req->type, key, &resultbuf, buffer, buflen, &hst, &ttl) != 0
	 && h_errno == NETDB_INTERNAL
	 && (errval = errno) == ERANGE)
    {
      errno = 0;

      if (__builtin_expect (buflen > 32768, 0))
	{
	  char *old_buffer = buffer;
	  buflen *= 2;
	  buffer = (char *) realloc (use_malloc ? buffer : NULL, buflen);
	  if (buffer == NULL)
	    {


	      hst = NULL;
	      buffer = old_buffer;


	      h_errno = TRY_AGAIN;
	      errval = EAGAIN;
	      break;
	    }
	  use_malloc = true;
	}
      else


	buffer = (char *) extend_alloca (buffer, buflen, 2 * buflen);
    }

  time_t timeout = cache_addhst (db, fd, req, key, hst, uid, he, dh,
				 h_errno == TRY_AGAIN ? errval : 0, ttl);

  if (use_malloc)
    free (buffer);

  return timeout;
}
