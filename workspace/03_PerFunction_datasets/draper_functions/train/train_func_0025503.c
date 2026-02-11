startConnection (void)
{
  struct sockaddr_in s;
#if HAVE_SOCKLEN_T
  socklen_t len;
#else
  int len;
#endif
  int access = ACCESS_UNKNOWN;

  len = sizeof (s);
  if (getpeername (0, (struct sockaddr *)&s, &len) < 0)
    {
      if (! isatty (0))
	{
	  log_msg (LOG_ERR, FALSE, "can't get peername %m", "?");
	  printf ("%d Why can't I figure out your name?  Later.\r\n",
		  CODE_NO_ACCESS);
	  access = ACCESS_DENY;
	}
      else
	{
	  current_host = "stdin";
	  current_addr = current_host;
	}
    }
  else
    {
      if ((s.sin_family != AF_INET) && (s.sin_family != AF_INET6))
	{
	  syslog (LOG_ERR, "%s: bad address family %ld",
		  "?", (long) s.sin_family);
	  printf ("%d You're a member of a bad address family.  Later.\r\n",
		  CODE_NO_ACCESS);
	  access = ACCESS_DENY;
	}
      else
	{
	  current_addr = (char *) inet_ntoa (s.sin_addr);
	  current_host = get_name (&s.sin_addr, s.sin_family);
	  if (current_host == NULL)
	    {
	      current_host = current_addr;
	    }
	}
    }
}
