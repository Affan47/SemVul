fsysdep_shell (qconn, zcmd, tcmd)
     struct sconnection *qconn;
     const char *zcmd;
     enum tshell_cmd tcmd;
{
  const char *azargs[4];
  int oread, owrite;
  int aidescs[3];
  pid_t ipid;

  if (tcmd != SHELL_NORMAL)
    azargs[0] = "/bin/sh";
  else
    {
      azargs[0] = getenv ("SHELL");
      if (azargs[0] == NULL)
	azargs[0] = "/bin/sh";
    }
  if (zcmd == NULL || *zcmd == '\0')
    azargs[1] = NULL;
  else
    {
      azargs[1] = "-c";
      azargs[2] = zcmd;
      azargs[3] = NULL;
    }

  if (qconn->qport == NULL)
    {
      oread = 0;
      owrite = 1;
    }
  else
    {
      switch (qconn->qport->uuconf_ttype)
	{
	default:
	  oread = owrite = -1;
	  break;
	case UUCONF_PORTTYPE_STDIN:
	case UUCONF_PORTTYPE_PIPE:
	  oread = ((struct ssysdep_conn *) qconn->psysdep)->ord;
	  owrite = ((struct ssysdep_conn *) qconn->psysdep)->owr;
	  break;
	case UUCONF_PORTTYPE_MODEM:
	case UUCONF_PORTTYPE_DIRECT:
	case UUCONF_PORTTYPE_TCP:
	case UUCONF_PORTTYPE_TLI:
	  oread = owrite = ((struct ssysdep_conn *) qconn->psysdep)->o;
	  break;
	}
    }

  aidescs[0] = 0;
  aidescs[1] = 1;
  aidescs[2] = 2;

  if (tcmd == SHELL_STDIN_FROM_PORT || tcmd == SHELL_STDIO_ON_PORT)
    aidescs[0] = oread;
  if (tcmd == SHELL_STDOUT_TO_PORT || tcmd == SHELL_STDIO_ON_PORT)
    aidescs[1] = owrite;

  ipid = ixsspawn (azargs, aidescs, FALSE, TRUE, (const char *) NULL,
		   FALSE, FALSE, (const char *) NULL,
		   (const char *) NULL, (const char *) NULL);
  if (ipid < 0)
    {
      ulog (LOG_ERROR, "ixsspawn (/bin/sh): %s", strerror (errno));
      return FALSE;
    }

  return ixswait ((unsigned long) ipid, "shell") == 0;
}
