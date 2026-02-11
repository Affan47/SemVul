user (const char *name)
{
  int ret;

  if (cred.logged_in)
    {
      if (cred.guest || cred.dochroot)
	{
	  reply (530, "Can't change user from guest login.");
	  return;
	}
      end_login (&cred);
    }


  ret = auth_user (name, &cred);
  if (!rfc2577 && ret != 0)
    {

      if (cred.message)
	{
	  reply (530, "%s", cred.message);
	  free (cred.message);
	  cred.message = NULL;
	}
      else
	reply (530, "User %s access denied.", name);
      if (logging)
	syslog (LOG_NOTICE, "FTP LOGIN REFUSED FROM %s, %s",
		cred.remotehost, name);
      return;
    }
  else if (rfc2577 && ret != 0)
    cred.delayed_reject = 1;
  else
    cred.delayed_reject = 0;


  if (rfc2577 && !cred.guest && cred.message)
    {
      free (cred.message);
      cred.message = NULL;
    }


  if (anon_only && !cred.guest && !cred.dochroot)
    {
      reply (530, "Sorry, only anonymous ftp allowed");
      return;
    }

  if (logging)
    {
      strncpy (curname, name, sizeof (curname) - 1);
      curname[sizeof (curname) - 1] = '\0';
    }

  if (cred.message)
    {


      char *msg = strrchr (cred.message, '\n');

      if (msg)
	msg++;
      else
	msg = cred.message;

      reply (331, "%s", msg);
      free (cred.message);
      cred.message = NULL;
    }
  else
    reply (331, "Password required for %s.", name);

  askpasswd = 1;


  if (login_attempts)
    sleep ((unsigned) login_attempts);
}
