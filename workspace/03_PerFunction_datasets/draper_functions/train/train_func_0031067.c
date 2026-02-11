getAuthUserResponse (EndPoint e, IoStatus i, Buffer *b, void *d)
{
  Connection cxn = (Connection) d ;
  int code ;
  char *p = bufferBase (b[0]) ;
  Buffer *buffers ;
  const char *peerName ;

  ASSERT (e == cxn->myEp) ;
  ASSERT (b [0] == cxn->respBuffer) ;
  ASSERT (b [1] == NULL) ;
  ASSERT (cxn->state == cxnConnectingS) ;
  VALIDATE_CONNECTION (cxn) ;

  peerName = hostPeerName (cxn->myHost) ;

  bufferAddNullByte (b[0]) ;

  d_printf (1,"%s:%d Processing authinfo user response: %s",
	    hostPeerName (cxn->myHost), cxn->ident, p) ;

  if (i == IoDone && writeIsPending (cxn->myEp))
    {

      warn ("%s:%d cxnsleep authinfo command still pending", peerName,
            cxn->ident) ;

      cxnSleepOrDie (cxn) ;
    }
  else if (i != IoDone)
    {
      if (i != IoEOF)
	{
	  errno = endPointErrno (e) ;
          syswarn ("%s:%d cxnsleep can't read response", peerName, cxn->ident);
	}
      cxnSleepOrDie (cxn) ;
    }
  else if (strchr (p, '\n') == NULL)
    {

      expandBuffer (b [0], BUFFER_EXPAND_AMOUNT) ;

      buffers = makeBufferArray (bufferTakeRef (b [0]), NULL) ;
      if ( !prepareRead (e, buffers, getAuthUserResponse, cxn, 1) )
	{
          warn ("%s:%d cxnsleep prepare read failed", peerName, cxn->ident) ;
	  freeBufferArray (buffers) ;
	  cxnSleepOrDie (cxn) ;
	}
    }
  else
    {
      clearTimer (cxn->readBlockedTimerId) ;

      if ( !getNntpResponse (p, &code, NULL) )
	{
          warn ("%s:%d cxnsleep response to AUTHINFO USER: %s", peerName,
                cxn->ident, p) ;

	  cxnSleepOrDie (cxn) ;
	}
      else
	{
          notice ("%s:%d connected", peerName, cxn->ident) ;

	  switch (code)
	    {
	    case 381:
	      issueAuthPass (e,cxn);
	      break ;

	    default:
              warn ("%s:%d cxnsleep response to AUTHINFO USER: %s", peerName,
                    cxn->ident, p) ;
	      cxn->authenticated = true;
	      issueModeStream (e,cxn);
	      break ;
	    }

	}
    }
}
