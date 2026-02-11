destroy(CORBA::Boolean etherealize_objects,
		    CORBA::Boolean wait_for_completion)
{
  CHECK_NOT_NIL();
  if( wait_for_completion ) {

    omniCurrent* current = omniCurrent::get();
    if (current && current->callDescriptor()) {


      OMNIORB_THROW(BAD_INV_ORDER,
		    BAD_INV_ORDER_WouldDeadLock,
		    CORBA::COMPLETED_NO);
    }
  }


  {
    pd_lock.lock();

    if( pd_destroyed ) {
      pd_lock.unlock ();
      OMNIORB_THROW(OBJECT_NOT_EXIST,
		    OBJECT_NOT_EXIST_POANotInitialised,
		    CORBA::COMPLETED_NO);
    }

    if( pd_dying ) {


      if( wait_for_completion ) {

	incrRefCount();

	while( pd_destroyed != 2 )  pd_deathSignal.wait();

	pd_lock.unlock ();
	decrRefCount();

      } else {
	pd_lock.unlock ();
      }
      return;
    }

    pd_dying = 1;

    pd_lock.unlock ();
  }

  {


    omni::internalLock->lock();

    int old_state = pd_rq_state;

    if (pd_rq_state == (int) PortableServer::POAManager::HOLDING)
      pd_rq_state = (int) PortableServer::POAManager::DISCARDING;

    omni::internalLock->unlock();

    if( old_state == (int) PortableServer::POAManager::HOLDING )
      pd_signal->broadcast();
  }


  if( omniORB::trace(10) ) {
    omniORB::logger l;
    l << "Destroying POA(" << (char*) pd_name << ").\n";
  }

  pd_manager->lose_poa(this);


  if( wait_for_completion ) {
    do_destroy(etherealize_objects);
  }
  else {
    omniORB::logs(15, "Starting a POA destroyer thread.");

    void** args = new void* [2];
    args[0] = (omniOrbPOA*) this;
    args[1] = (void*) (unsigned long) etherealize_objects;

    try {
      (new omni_thread(destroyer_thread_fn, args))->start();
    }
    catch (const omni_thread_fatal& ex) {
      if (omniORB::trace(1)) {
	omniORB::logger log;
	log << "Unable to start POA destroyer thread (error "
	    << ex.error << ").\n";
      }
      OMNIORB_THROW(NO_RESOURCES,
		    NO_RESOURCES_UnableToStartThread,
		    CORBA::COMPLETED_NO);
    }
  }
}
