_cupsSetDefaults(void)
{
  cups_file_t	*fp;
  const char	*home,
		*cups_encryption,
		*cups_server,
		*cups_user,
#ifdef HAVE_GSSAPI
		*cups_gssservicename,
#endif
		*cups_anyroot,
		*cups_expiredroot,
		*cups_expiredcerts;
  char		filename[1024];
  _cups_globals_t *cg = _cupsGlobals();


  DEBUG_puts("_cupsSetDefaults()");


  cups_encryption     = getenv("CUPS_ENCRYPTION");
  cups_server	      = getenv("CUPS_SERVER");
#ifdef HAVE_GSSAPI
  cups_gssservicename = getenv("CUPS_GSSSERVICENAME");
#endif
  cups_anyroot	      = getenv("CUPS_ANYROOT");
  cups_expiredroot    = getenv("CUPS_EXPIREDROOT");
  cups_expiredcerts   = getenv("CUPS_EXPIREDCERTS");

  if ((cups_user = getenv("CUPS_USER")) == NULL)
  {
#ifndef WIN32


    if ((cups_user = getenv("USER")) != NULL)
    {


      struct passwd	*pw;

      if ((pw = getpwnam(cups_user)) == NULL || pw->pw_uid != getuid())
        cups_user = NULL;
    }
#endif
  }


  if (cg->encryption == (http_encryption_t)-1 || !cg->server[0] ||
      !cg->user[0] || !cg->ipp_port)
  {
#  ifdef HAVE_GETEUID
    if ((geteuid() == getuid() || !getuid()) && getegid() == getgid() && (home = getenv("HOME")) != NULL)
#  elif !defined(WIN32)
    if (getuid() && (home = getenv("HOME")) != NULL)
#  else
    if ((home = getenv("HOME")) != NULL)
#  endif
    {


      snprintf(filename, sizeof(filename), "%s/.cups/client.conf", home);
      fp = cupsFileOpen(filename, "r");
    }
    else
      fp = NULL;

    if (!fp)
    {


      snprintf(filename, sizeof(filename), "%s/client.conf",
               cg->cups_serverroot);
      fp = cupsFileOpen(filename, "r");
    }


    cups_read_client_conf(fp, cg, cups_encryption, cups_server, cups_user,
#ifdef HAVE_GSSAPI
			  cups_gssservicename,
#endif
			  cups_anyroot, cups_expiredroot,
			  cups_expiredcerts);
    cupsFileClose(fp);
  }
}
