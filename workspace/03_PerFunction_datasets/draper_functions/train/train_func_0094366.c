doit (struct sockaddr *sap, socklen_t salen)
{
  struct passwd *pw;
  char user[64], passwd[64];
  char *xpasswd;

  alarm (60);
  printf ("login: ");
  fflush (stdout);
  if (readline (user, sizeof (user)) < 0)
    {
      fprintf (stderr, "user read\n");
      return;
    }
  user[sizeof (user) - 1] = '\0';

  pw = getpwnam (user);
  if (pw == NULL)
    {


      printf ("Password: ");
      fflush (stdout);
      if (readline (passwd, sizeof (passwd)) < 0)
	{
	  fprintf (stderr, "passwd read\n");
	  return;
	}
      fprintf (stderr, "Login incorrect.");
      return;
    }
  if (pw->pw_passwd && *pw->pw_passwd != '\0')
    {
      printf ("Password: ");
      fflush (stdout);
      if (readline (passwd, sizeof (passwd)) < 0)
	{
	  fprintf (stderr, "passwd read\n");
	  return;
	}
      xpasswd = crypt (passwd, pw->pw_passwd);
      if (strcmp (xpasswd, pw->pw_passwd))
	{
	  fprintf (stderr, "Login incorrect.");
	  return;
	}
    }


  if (strcmp (pw->pw_shell, uucico_location))
    {
      fprintf (stderr, "Login incorrect.");
      return;
    }

  alarm (0);
  sprintf (Username, "USER=%s", user);
  sprintf (Logname, "LOGNAME=%s", user);
  dologin (pw, sap, salen);
  setgid (pw->pw_gid);
#ifdef HAVE_INITGROUPS
  initgroups (pw->pw_name, pw->pw_gid);
#endif
  if (chdir (pw->pw_dir) < 0)
    {
      fprintf (stderr, "Login incorrect.");
      return;
    }
  setuid (pw->pw_uid);
  execl (uucico_location, "uucico", NULL);
  perror ("uucico server: execl");
}
