dispose(omniIdentity* id)
{
  ASSERT_OMNI_TRACEDMUTEX_HELD(boa_lock, 1);
  ASSERT_OMNI_TRACEDMUTEX_HELD(*omni::internalLock, 1);

  if( pd_state == DESTROYED ) {
    omni::internalLock->unlock();
    boa_lock.unlock();
    OMNIORB_THROW(OBJECT_NOT_EXIST,OBJECT_NOT_EXIST_NoMatch,
		  CORBA::COMPLETED_NO);
  }

  omniObjTableEntry* entry = omniObjTableEntry::downcast(id);

  if( !entry || entry->state() != omniObjTableEntry::ACTIVE ) {
    omni::internalLock->unlock();
    boa_lock.unlock();
    return;
  }

  entry->setDeactivating();
  entry->removeFromOAObjList();

  if( entry->is_idle() ) {
    detached_object();
    boa_lock.unlock();
    lastInvocationHasCompleted(entry);
  }
  else {


    omni::internalLock->unlock();
    detached_object();
    boa_lock.unlock();

    omniORB::logs(15, "Object is still busy -- etherealise later.");
  }
}
