_obj_is_ready()
{
  boa_lock.lock();

  if( !the_boa ) {
    boa_lock.unlock();
    OMNIORB_THROW(OBJ_ADAPTER,OBJ_ADAPTER_BOANotInitialised,
		  CORBA::COMPLETED_NO);
  }

  omniObjKey key((const CORBA::Octet*) &pd_key, sizeof(omniOrbBoaKey));

  omni::internalLock->lock();

  omniObjTableEntry* entry = omniObjTable::newEntry(key);

  if( !entry ) {
    omni::internalLock->unlock();
    boa_lock.unlock();
    OMNIORB_THROW(OBJECT_NOT_EXIST,
		  OBJECT_NOT_EXIST_NoMatch, CORBA::COMPLETED_NO);
  }

  entry->setActive(this, the_boa);

  omni::internalLock->unlock();
  entry->insertIntoOAObjList(the_boa->activeObjList());
  boa_lock.unlock();
}
