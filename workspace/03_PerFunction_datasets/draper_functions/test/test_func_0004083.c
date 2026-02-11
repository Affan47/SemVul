initReadBlockedTimeout (Connection cxn)
{
  ASSERT (cxn != NULL) ;
ASSERT (cxn->state != cxnIdleS ) ;


  clearTimer (cxn->readBlockedTimerId) ;

  if (cxn->readTimeout > 0)
    cxn->readBlockedTimerId = prepareSleep (responseTimeoutCbk, cxn->readTimeout, cxn) ;
}
