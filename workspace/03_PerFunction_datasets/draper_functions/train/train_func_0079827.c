auth_user (const char *name, struct credentials *pcred)
{
  int err = 0;

  pcred->guest = 0;
  pcred->expired = AUTH_EXPIRED_NOT;

  switch (pcred->auth_type)
    {
#ifdef WITH_LINUX_PAM
    case AUTH_TYPE_PAM:
      err = pam_user (name, pcred);
      break;
#endif
#ifdef WITH_KERBEROS
    case AUTH_TYPE_KERBEROS:
      err = -1;
      break;
#endif
#ifdef WITH_KERBEROS5
    case AUTH_TYPE_KERBEROS5:
      err = -1;
      break;
#endif
#ifdef WITH_OPIE
    case AUTH_TYPE_OPIE:
      err = -1;
      break;
#endif
    case AUTH_TYPE_PASSWD:
    default:
      {
	size_t len;
	free (pcred->message);
	len = (size_t) (64 + strlen (name));
	pcred->message = malloc (len);
	if (pcred->message == NULL)
	  return -1;


	if (strcmp (name, "ftp") == 0 || strcmp (name, "anonymous") == 0)
	  {
	    if (checkuser (PATH_FTPUSERS, "ftp")
		|| checkuser (PATH_FTPUSERS, "anonymous"))
	      {
		snprintf (pcred->message, len, "User %s access denied.",
			  name);
		err = 1;
	      }
	    else if (sgetcred ("ftp", pcred) == 0)
	      {
		pcred->guest = 1;
		strcpy (pcred->message,
			"Guest login ok, type your name as password.");
	      }
	    else
	      {
		snprintf (pcred->message, len, "User %s unknown.", name);
		err = 1;
	      }
	    return err;
	  }

	if (sgetcred (name, pcred) == 0)
	  {
	    const char *cp;
	    const char *shell;


	    shell = pcred->shell;
	    if (shell == NULL || *shell == 0)
	      shell = PATH_BSHELL;
	    setusershell ();
	    while ((cp = getusershell ()) != NULL)
	      if (strcmp (cp, shell) == 0)
		break;
	    endusershell ();

	    if (cp == NULL || checkuser (PATH_FTPUSERS, name))
	      {
		sprintf (pcred->message, "User %s access denied.", name);
		return 1;
	      }
	  }
	else
	  {
	    free (pcred->message);
	    pcred->message = NULL;
	    return 1;
	  }
	snprintf (pcred->message, len,
		  "Password required for %s.", pcred->name);
	err = 0;
      }
    }

  if (err == 0)
    {
      pcred->dochroot = checkuser (PATH_FTPCHROOT, pcred->name);

#if defined WITH_PAM && !defined WITH_LINUX_PAM
      if (pcred->auth_type == AUTH_TYPE_PAM)
	err = pam_user (name, pcred);
#endif
    }

  return err;
}
