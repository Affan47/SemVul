impl_is_ready(CORBA::ImplementationDef_ptr,
			  CORBA::Boolean dont_block)
{
  if( _NP_is_nil() )  _CORBA_invoked_nil_pseudo_ref();

  int state_changed = 0;
  boa_lock.lock();
  {
    omni::internalLock->lock();

    switch( pd_state ) {
    case IDLE:
      state_changed = 1;
      pd_state = ACTIVE;
      break;

    case ACTIVE:
      break;

    case DESTROYED:
      omni::internalLock->unlock();
      boa_lock.unlock();
      OMNIORB_THROW(OBJECT_NOT_EXIST,OBJECT_NOT_EXIST_BOANotInitialised,
		    CORBA::COMPLETED_NO);
      break;
    }

    omni::internalLock->unlock();
  }

  if( state_changed ) {
    try { adapterActive(); }
    catch(...) {
      boa_lock.unlock();
      throw;
    }


    if(  1 )  pd_state_signal->broadcast();
  }

  if( !dont_block ) {
    pd_nblocked++;

    omni::internalLock->lock();
    boa_lock.unlock();
    pd_state_signal->wait();
    omni::internalLock->unlock();

    boa_lock.lock();
    --pd_nblocked;
    boa_lock.unlock();
  }
  else
    boa_lock.unlock();
}
