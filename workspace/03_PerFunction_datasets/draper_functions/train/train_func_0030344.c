PR_streamToRead() const
{
  if (!pd_mbuf) {

    if (!pd_marshal)
      OMNIORB_THROW(BAD_PARAM, BAD_PARAM_InvalidAny, CORBA::COMPLETED_NO);

    cdrAnyMemoryStream* mbuf = new cdrAnyMemoryStream;

    pd_marshal(*mbuf, pd_data);

    {
      omni_tracedmutex_lock l(anyLock);

      if (pd_mbuf) {

	delete mbuf;
      }
      else {
	CORBA::Any* me = OMNI_CONST_CAST(CORBA::Any*, this);
	me->pd_mbuf = mbuf;
      }
    }
  }
  return *pd_mbuf;
}
