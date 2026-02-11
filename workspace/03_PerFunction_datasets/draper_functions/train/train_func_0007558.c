shutDown (InnListener l)
{
  u_int i ;
  u_int count ;

  dprintf (1,"Shutting down the listener\n") ;

  closeDroppedArticleFile () ;
  unlink (pidFile) ;

  if (l->myep != NULL)
    {
      if (l->inputEOFSleepId != 0)
	removeTimeout (l->inputEOFSleepId) ;
      l->inputEOFSleepId = 0 ;
      delEndPoint (l->myep) ;
    }
  l->myep = NULL ;

  for (i = 0, count = 0 ; i < l->hostLen ; i++)
    if (l->myHosts [i] != NULL)
      {
        hostClose (l->myHosts[i]) ;
        count++ ;
      }

  if (count == 0 || fastExit)
    {
      time_t now = theTime () ;
      char dateString [30] ;

      strcpy (dateString,ctime (&now)) ;
      dateString [24] = '\0' ;

      if (fastExit)
        syslog (LOG_NOTICE,FAST_EXIT_PROGRAM,dateString) ;
      else
        syslog (LOG_NOTICE,STOPPING_PROGRAM,dateString) ;

      exit (0) ;
    }
}
