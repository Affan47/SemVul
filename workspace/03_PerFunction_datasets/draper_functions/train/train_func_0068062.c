ftcp_close (qconn, puuconf, qdialer, fsuccess)
     struct sconnection *qconn;
     pointer puuconf ATTRIBUTE_UNUSED;
     struct uuconf_dialer *qdialer ATTRIBUTE_UNUSED;
     boolean fsuccess ATTRIBUTE_UNUSED;
{
  struct ssysdep_conn *qsysdep;
  boolean fret;

  qsysdep = (struct ssysdep_conn *) qconn->psysdep;
  fret = TRUE;
  if (qsysdep->o >= 0 && close (qsysdep->o) < 0)
    {
      ulog (LOG_ERROR, "close: %s", strerror (errno));
      fret = FALSE;
    }
  qsysdep->o = -1;


  if (qsysdep->ipid != getpid ())
    fret = FALSE;

  return fret;
}
