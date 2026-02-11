issueModeStream (EndPoint e, Connection cxn)
{
  Buffer *modeCmdBuffers,*readBuffers ;
  Buffer modeBuffer ;
  char *p;

#define  MODE_CMD "MODE STREAM\r\n"

  modeBuffer = newBuffer (strlen (MODE_CMD) + 1) ;
  p = bufferBase (modeBuffer) ;


  d_printf (1,"%s:%d Issuing the streaming command: %s\n",
	    hostPeerName (cxn->myHost),cxn->ident,MODE_CMD) ;

  strlcpy (p, MODE_CMD, bufferSize (modeBuffer)) ;

  bufferSetDataSize (modeBuffer, strlen (p)) ;

  modeCmdBuffers = makeBufferArray (modeBuffer, NULL) ;

  if ( !prepareWriteWithTimeout (e, modeCmdBuffers, modeCmdIssued,
				 cxn) )
    {
      die ("%s:%d fatal prepare write for mode stream failed",
           hostPeerName (cxn->myHost), cxn->ident) ;
    }

  bufferSetDataSize (cxn->respBuffer, 0) ;

  readBuffers = makeBufferArray (bufferTakeRef(cxn->respBuffer),NULL);

  if ( !prepareRead (e, readBuffers, getModeResponse, cxn, 1) )
    {
      warn ("%s:%d cxnsleep prepare read failed", hostPeerName (cxn->myHost),
            cxn->ident) ;
      freeBufferArray (readBuffers) ;
      cxnSleepOrDie (cxn) ;
    }
}
