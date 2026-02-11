processResponse400 (Connection cxn, char *response)
{
  if (!(cxn->state == cxnFlushingS ||
        cxn->state == cxnFeedingS ||
        cxn->state == cxnIdleS ||
        cxn->state == cxnClosingS))
    {
      syslog (LOG_ERR,CXN_BAD_STATE,hostPeerName (cxn->myHost),
              cxn->ident,stateToString (cxn->state)) ;
      cxnSleepOrDie (cxn) ;
      return ;
    }

  VALIDATE_CONNECTION (cxn) ;


  syslog (LOG_NOTICE,CXN_BLOCKED,hostPeerName(cxn->myHost),cxn->ident,
          response) ;


  if (writeIsPending (cxn->myEp))
    cxnSleepOrDie (cxn) ;
  else
    {
      if (cxn->articleQTotal > 0)
        {


          deferAllArticles (cxn) ;
          clearTimer (cxn->readBlockedTimerId) ;

          cxnIdle (cxn) ;
        }


      cxnSleepOrDie (cxn) ;
    }
}
