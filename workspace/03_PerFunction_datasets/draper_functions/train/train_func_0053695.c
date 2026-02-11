synchronise_request(omniLocalIdentity* lid)
{
  ASSERT_OMNI_TRACEDMUTEX_HELD(*omni::internalLock, 1);


  while( pd_rq_state == (int) PortableServer::POAManager::HOLDING ) {
    if (omniORB::trace(15)) {
      omniORB::logger l;
      l << "POA for " << lid << " in HOLDING state; waiting...\n";
    }
    if( orbParameters::poaHoldRequestTimeout ) {
      unsigned long sec, nsec;
      omni_thread::get_time(&sec, &nsec,
			    orbParameters::poaHoldRequestTimeout/1000,
			    (orbParameters::poaHoldRequestTimeout%1000)*1000000);
      if( !pd_signal->timedwait(sec, nsec) ) {


	startRequest();
	omni::internalLock->unlock();
	OMNIORB_THROW(TRANSIENT, TRANSIENT_CallTimedout, CORBA::COMPLETED_NO);
      }
    }
    else
      pd_signal->wait();
  }

  switch( pd_rq_state ) {
  case (int) PortableServer::POAManager::HOLDING:
    OMNIORB_ASSERT(0);

  case (int) PortableServer::POAManager::ACTIVE:
    break;

  case (int) PortableServer::POAManager::DISCARDING:


    startRequest();
    omni::internalLock->unlock();
    OMNIORB_THROW(TRANSIENT, TRANSIENT_POANoResource, CORBA::COMPLETED_NO);

  case (int) PortableServer::POAManager::INACTIVE:


    startRequest();
    omni::internalLock->unlock();


    OMNIORB_THROW(OBJ_ADAPTER,
		  OBJ_ADAPTER_POAUnknownAdapter,
		  CORBA::COMPLETED_NO);
  }


  CORBA::Boolean deactivated;
  pd_lock.lock();
  deactivated = lid->deactivated();
  pd_lock.unlock();

  if (deactivated) {


    startRequest();
    omni::internalLock->unlock();
    OMNIORB_THROW(TRANSIENT,
		  TRANSIENT_ObjDeactivatedWhileHolding,
		  CORBA::COMPLETED_NO);
  }
}
