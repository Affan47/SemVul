quitWritten (EndPoint e, IoStatus i, Buffer *b, void *d)
{
  Connection cxn = (Connection) d ;
  const char *peerName ;

  peerName = hostPeerName (cxn->myHost) ;

  clearTimer (cxn->writeBlockedTimerId) ;

  ASSERT (cxn->myEp == e) ;
  VALIDATE_CONNECTION (cxn) ;

  if (i != IoDone)
    {
      errno = endPointErrno (e) ;
      syslog (LOG_ERR, QUIT_WRITE_FAILED, peerName, cxn->ident) ;
      if (cxn->state == cxnClosingS)
        {
          cxnDead (cxn) ;
          delConnection (cxn) ;
        }
      else
        cxnWait (cxn) ;
    }
  else

    initReadBlockedTimeout (cxn) ;

  freeBufferArray (b) ;
}
