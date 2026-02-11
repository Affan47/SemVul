pthread_tryjoin_np(pthread_t thread, void **retval)
{
  int ret;
  if (!dmtcp::VirtualPidTable::instance().beginPthreadJoin(thread)) {
    return EINVAL;
  }

  WRAPPER_EXECUTION_DISABLE_CKPT();
  ret = _real_pthread_tryjoin_np(thread, retval);
  WRAPPER_EXECUTION_ENABLE_CKPT();

  dmtcp::VirtualPidTable::instance().endPthreadJoin(thread);
  return ret;
}
