_NP_incrRefCount()
{
  OMNIORB_ASSERT(!_NP_is_nil());

  omni::poRcLock->lock();
  pd_refCount++;
  omni::poRcLock->unlock();
}
