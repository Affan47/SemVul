hostCxnSleeping (Host host, Connection cxn)
{
  unsigned int i ;

  for (i = 0 ; i < host->maxConnections ; i++)
    if (host->connections [i] == cxn)
      {
        if (!host->cxnSleeping [i])
          {
            host->cxnSleeping [i] = true ;
            host->sleepingCxns++ ;
          }

        if (host->spoolTime == 0 && host->sleepingCxns >= host->maxConnections)
          hostStartSpooling (host) ;

        break ;
      }

  ASSERT (i < host->maxConnections) ;

  hostLogStatus () ;
}
