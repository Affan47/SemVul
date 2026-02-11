hostCxnBlocked (Host host, Connection cxn, char *reason)
{
  ASSERT(host->params != NULL);
#ifndef NDEBUG
  {
    unsigned int i ;

    for (i = 0 ; i < host->maxConnections ; i++)
      if (host->connections [i] == cxn)
        ASSERT (host->cxnActive [i] == false) ;
  }
#endif

  if (host->blockedReason == NULL)
    host->blockedReason = xstrdup (reason) ;

  if (host->activeCxns == 0 && host->spoolTime == 0)
    {
      host->blockedCxn = cxn ;
      notice ("%s remote cannot accept articles initial: %s",
              host->params->peerName, reason) ;
    }
  else if (host->activeCxns > 0 && !host->notifiedChangedRemBlckd)
    {
      notice ("%s remote cannot accept articles change: %s",
              host->params->peerName, reason) ;
      host->notifiedChangedRemBlckd = true ;
    }
  else if (host->spoolTime != 0 && host->blockedCxn == cxn)
    {
      notice ("%s remote cannot accept articles still: %s",
              host->params->peerName, reason) ;
    }

}
