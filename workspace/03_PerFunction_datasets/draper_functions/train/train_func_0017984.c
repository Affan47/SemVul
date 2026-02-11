env_init (void)
{
  extern char **environ;
  register char **epp, *cp;
  register struct env_lst *ep;
#ifndef strchr
  extern char *strchr (const char *, int);
#endif

  for (epp = environ; *epp; epp++)
    {
      cp = strchr (*epp, '=');
      if (cp)
	{
	  *cp = '\0';
	  ep = env_define (*epp, (unsigned char *) cp + 1);
	  ep->export = 0;
	  *cp = '=';
	}
    }


  if ((ep = env_find ("DISPLAY"))
      && ((*ep->value == ':')
	  || (strncmp ((char *) ep->value, "unix:", 5) == 0)))
    {
      char *hostname = localhost ();
      char *cp2 = strchr ((char *) ep->value, ':');

      cp = xmalloc (strlen (hostname) + strlen (cp2) + 1);
      sprintf (cp, "%s%s", hostname, cp2);

      free (ep->value);
      ep->value = (unsigned char *) cp;

      free (hostname);
    }


  if ((env_find ("USER") == NULL) && (ep = env_find ("LOGNAME")))
    {
      env_define ("USER", ep->value);
      env_unexport ("USER");
    }
  env_export ("DISPLAY");
  env_export ("PRINTER");
}
