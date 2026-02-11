processResponse436 (Connection cxn, char *response)
{
  ArtHolder artHolder ;

  (void) response ;

  if (cxn->doesStreaming)
    {
      syslog (LOG_ERR,CXN_NONSTREAM_RESP,hostPeerName (cxn->myHost),
              cxn->ident,response) ;
      cxnSleepOrDie (cxn) ;
      return ;
    }

  if (!(cxn->state == cxnFlushingS ||
        cxn->state == cxnFeedingS ||
        cxn->state == cxnClosingS))
    {
      syslog (LOG_ERR,CXN_BAD_STATE,hostPeerName (cxn->myHost),
              cxn->ident,stateToString (cxn->state)) ;
      cxnSleepOrDie (cxn) ;
      return ;
    }

  ASSERT (cxn->articleQTotal == 1) ;
  ASSERT (cxn->takeRespHead != NULL || cxn->checkRespHead != NULL) ;
  VALIDATE_CONNECTION (cxn) ;

  cxn->articleQTotal-- ;

  if (cxn->takeRespHead != NULL)
    {
      artHolder = cxn->takeRespHead ;
      cxn->takeRespHead = NULL ;
    }
  else
    {
      artHolder = cxn->checkRespHead ;
      cxn->checkRespHead = NULL ;
    }


  if (cxn->articleQTotal == 0 && !writeIsPending(cxn->myEp))
    cxnIdle (cxn) ;

  hostArticleDeferred (cxn->myHost, cxn, artHolder->article) ;
  delArtHolder (artHolder) ;
}
