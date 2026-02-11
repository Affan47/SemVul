issueStreamingCommands (Connection cxn)
{
  Buffer checkBuffer = NULL ;
  Buffer *writeArray = NULL ;
  ArtHolder p, q ;
  bool rval = false ;

  ASSERT (cxn != NULL) ;
  ASSERT (cxn->myEp != NULL) ;
  ASSERT (cxn->doesStreaming) ;
  VALIDATE_CONNECTION (cxn) ;

  checkBuffer = buildCheckBuffer (cxn) ;

  if (checkBuffer != NULL)
    {

      for (p = cxn->checkRespHead ; p != NULL && p->next != NULL ; p = p->next)
         ;

      if (p == NULL)
        cxn->checkRespHead = cxn->checkHead ;
      else
        p->next = cxn->checkHead ;

      cxn->checkHead = NULL ;
    }


  writeArray = buildTakethisBuffers (cxn,checkBuffer) ;


  if (writeArray)
    {
      if ( !prepareWriteWithTimeout (cxn->myEp, writeArray,
                                     commandWriteDone, cxn) )
        {
          syslog (LOG_ERR, PREPARE_WRITE_FAILED,
                  hostPeerName (cxn->myHost), cxn->ident) ;
          die ("Prepare write for STREAMING commands failed") ;
        }

      rval = true ;


      for (p = cxn->takeRespHead ; p != NULL && p->next != NULL ; p = p->next)
         ;

      if (p == NULL)
        cxn->takeRespHead = cxn->takeHead ;
      else
        p->next = cxn->takeHead ;

      cxn->takeHead = NULL ;
    }


  if (cxn->missing && cxn->articleQTotal == 0)
    cxnIdle (cxn) ;
  for (p = cxn->missing ; p != NULL ; p = q)
    {
      hostArticleIsMissing (cxn->myHost, cxn, p->article) ;
      q = p->next ;
      delArtHolder (p) ;
    }
  cxn->missing = NULL ;

  return rval ;
}
