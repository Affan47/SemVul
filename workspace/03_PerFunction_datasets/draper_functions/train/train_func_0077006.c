growPollLists()
{
  ASSERT_OMNI_TRACEDMUTEX_HELD(pd_collection_lock, 1);


  struct pollfd* new_pollfds     = new struct pollfd[pd_pollfd_len*2];
  SocketHolder** new_pollsockets = new SocketHolder*[pd_pollfd_len*2];

  for (unsigned i=0; i < pd_pollfd_len; i++) {
    new_pollfds[i]     = pd_pollfds[i];
    new_pollsockets[i] = pd_pollsockets[i];
  }
  delete [] pd_pollfds;
  delete [] pd_pollsockets;

  pd_pollfds     = new_pollfds;
  pd_pollsockets = new_pollsockets;
  pd_pollfd_len  = pd_pollfd_len * 2;
}
