fgsend_acks (qdaemon)
     struct sdaemon *qdaemon;
{
  while (iGlocal_ack != iGrecseq)
    {
      iGlocal_ack = INEXTSEQ (iGlocal_ack);
      if (! fgsend_control (qdaemon, RR, iGlocal_ack))
	return FALSE;
    }
  return TRUE;
}
