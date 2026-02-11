fspipe_close (qconn, puuconf, qdialer, fsuccess)
     struct sconnection *qconn;
     pointer puuconf ATTRIBUTE_UNUSED;
     struct uuconf_dialer *qdialer ATTRIBUTE_UNUSED;
     boolean fsuccess ATTRIBUTE_UNUSED;
{
  struct ssysdep_conn *qsysdep;
  boolean fret;

  qsysdep = (struct ssysdep_conn *) qconn->psysdep;
  fret = TRUE;


  if (qsysdep->ord >= 0 && close (qsysdep->ord) < 0)
    {
      ulog (LOG_ERROR, "fspipe_close: close read fd: %s", strerror (errno));
      fret = FALSE;
    }
  if (qsysdep->owr != qsysdep->ord
      && qsysdep->owr >= 0
      && close (qsysdep->owr) < 0)
    {
      ulog (LOG_ERROR, "fspipe_close: close write fd: %s", strerror (errno));
      fret = FALSE;
    }
  qsysdep->ord = -1;
  qsysdep->owr = -1;


  if (qsysdep->ipid >= 0)
    {
      if (kill (qsysdep->ipid, SIGHUP) == 0)
        usysdep_sleep (2);
#ifdef SIGPIPE
      if (kill (qsysdep->ipid, SIGPIPE) == 0)
        usysdep_sleep (2);
#endif
      if (kill (qsysdep->ipid, SIGKILL) < 0 && errno == EPERM)
	{
	  ulog (LOG_ERROR, "fspipe_close: Cannot kill child pid %lu: %s",
		(unsigned long) qsysdep->ipid, strerror (errno));
	  fret = FALSE;
	}
      else
	(void) ixswait ((unsigned long) qsysdep->ipid, (const char *) NULL);
    }
  qsysdep->ipid = -1;
  return fret;
}
