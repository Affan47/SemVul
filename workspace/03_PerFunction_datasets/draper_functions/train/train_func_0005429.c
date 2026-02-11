frec_file_send_confirm (qtrans, qdaemon)
     struct stransfer *qtrans;
     struct sdaemon *qdaemon;
{
  struct srecinfo *qinfo = (struct srecinfo *) qtrans->pinfo;
  const char *zsend;
  int ilocal, iremote;

  if (! qinfo->fmoved)
    zsend = "CN5";
  else if (! qdaemon->frequest_hangup)
    zsend = "CY";
  else
    {
#if DEBUG > 0
      if (qdaemon->fmaster)
	ulog (LOG_FATAL, "frec_file_send_confirm: Can't happen");
#endif

      DEBUG_MESSAGE0 (DEBUG_UUCP_PROTO,
		      "frec_send_file_confirm: Requesting remote to transfer control");
      zsend = "CYM";
    }


  if (! qinfo->flocal && qinfo->fmoved)
    usent_receive_ack (qdaemon, qtrans);

  ilocal = qtrans->ilocal;
  iremote = qtrans->iremote;

  urrec_free (qtrans);

  return (*qdaemon->qproto->pfsendcmd) (qdaemon, zsend, ilocal, iremote);
}
