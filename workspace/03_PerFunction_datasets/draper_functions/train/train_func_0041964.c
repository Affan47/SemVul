prepareDmtcpWrappers()
{

  JALLOC_HELPER_DISABLE_LOCKS();
  dmtcp_wrappers_initializing = 1;
  initialize_libc_wrappers();

  dmtcp_wrappers_initializing = 0;
  initialize_libpthread_wrappers();
  JALLOC_HELPER_ENABLE_LOCKS();


  JASSERT(pthread_atfork(pthread_atfork_prepare,
                         pthread_atfork_parent,
                         pthread_atfork_child) == 0);
}
