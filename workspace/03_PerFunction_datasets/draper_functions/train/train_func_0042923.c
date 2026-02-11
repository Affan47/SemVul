setActive(omniServant* servant, omniObjAdapter* adapter)
{
  ASSERT_OMNI_TRACEDMUTEX_HELD(*omni::internalLock, 1);
  OMNIORB_ASSERT(pd_state == ACTIVATING);

  setServant(servant, adapter);
  servant->_addActivation(this);

  if( omniORB::trace(15) ) {
    omniORB::logger l;
    l << "State " << this << " -> active\n";
  }

  pd_state = ACTIVE;

  if (pd_waiters)
    pd_cond->broadcast();
}
