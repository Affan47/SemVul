login (char *host)
{
  char tmp[80];
  char *user, *pass, *acct;
  int n, aflag = 0;

  user = pass = acct = 0;
  if (remote_userpass (host, &user, &pass, &acct) < 0)
    {
      code = -1;
      return (0);
    }
  while (user == NULL)
    {
      char *myname = getlogin ();

      if (myname == NULL)
	{
	  struct passwd *pp = getpwuid (getuid ());

	  if (pp != NULL)
	    myname = pp->pw_name;
	}
      if (myname)
	printf ("Name (%s:%s): ", host, myname);
      else
	printf ("Name (%s): ", host);
      if (fgets (tmp, sizeof (tmp) - 1, stdin))
	{


	  tmp[strlen (tmp) - 1] = '\0';
	}
      else
	*tmp = '\0';
      if (*tmp == '\0')
	user = myname;
      else
	user = tmp;
    }
  n = command ("USER %s", user);
  if (n == CONTINUE)
    {
      if (pass == NULL)
	pass = getpass ("Password:");
      n = command ("PASS %s", pass);
      if (pass)
	memset (pass, 0, strlen (pass));
    }
  if (n == CONTINUE)
    {
      aflag++;
      acct = getpass ("Account:");
      n = command ("ACCT %s", acct);
      if (acct)
	memset (acct, 0, strlen (acct));
    }
  if (n != COMPLETE)
    {
      error (0, 0, "Login failed.");
      return (0);
    }
  if (!aflag && acct != NULL)
    {
      command ("ACCT %s", acct);
      memset (acct, 0, strlen (acct));
    }
  if (proxy)
    return (1);
  for (n = 0; n < macnum; ++n)
    {
      if (!strcmp ("init", macros[n].mac_name))
	{
	  free (line);
	  line = calloc (MAXLINE, sizeof (*line));
	  linelen = MAXLINE;
	  if (!line)
	    quit (0, 0);


	  strcpy (line, "$init");
	  makeargv ();
	  domacro (margc, margv);
	  break;
	}
    }
  return (1);
}
