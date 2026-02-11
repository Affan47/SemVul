cxnTerminate (Connection cxn)
{
  ASSERT (cxn != NULL) ;
  ASSERT (cxn->state != cxnDeadS) ;
  ASSERT (cxn->state != cxnStartingS) ;
  VALIDATE_CONNECTION (cxn) ;

  switch (cxn->state)
    {
      case cxnFeedingS:
        dprintf (1,"%s:%d Issuing terminate\n",
                 hostPeerName (cxn->myHost), cxn->ident) ;

        clearTimer (cxn->flushTimerId) ;

        cxn->state = cxnClosingS ;

        deferQueuedArticles (cxn) ;
        if (cxn->articleQTotal == 0)
          issueQUIT (cxn) ;
        break ;

      case cxnIdleTimeoutS:
      case cxnIdleS:
        ASSERT (cxn->articleQTotal == 0) ;
        if (cxn->state != cxnIdleTimeoutS)
          clearTimer (cxn->artReceiptTimerId) ;
        clearTimer (cxn->flushTimerId) ;
        cxn->state = cxnClosingS ;
        issueQUIT (cxn) ;
        break ;

      case cxnFlushingS:
        dprintf (1,"%s:%d Connection already being flushed\n",
                 hostPeerName (cxn->myHost),cxn->ident);
        cxn->state = cxnClosingS ;
        if (cxn->articleQTotal == 0)
          issueQUIT (cxn) ;
        break ;

      case cxnClosingS:
        dprintf (1,"%s:%d Connection already closing\n",
                 hostPeerName (cxn->myHost),cxn->ident) ;
        break ;

      case cxnWaitingS:
      case cxnConnectingS:
      case cxnSleepingS:
        cxnDead (cxn) ;
        break ;

      default:
        die ("Bad connection state: %s\n",stateToString (cxn->state)) ;
    }

  VALIDATE_CONNECTION (cxn) ;

  if (cxn->state == cxnDeadS)
    {
      dprintf (1,"%s:%d Deleting connection\n",hostPeerName (cxn->myHost),
               cxn->ident) ;

      delConnection (cxn) ;
    }
}
