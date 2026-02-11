curlSocketCallback(CURL *easy, curl_socket_t s, int action,
                              void *userp, void *socketp)
{
  struct ReadWriteSockets* sockets = userp;

  (void)easy;
  (void)socketp;

  if (action == CURL_POLL_IN || action == CURL_POLL_INOUT)
    addFd(&sockets->read, s, "read");

  if (action == CURL_POLL_OUT || action == CURL_POLL_INOUT)
    addFd(&sockets->write, s, "write");

  if(action == CURL_POLL_REMOVE) {
    removeFd(&sockets->read, s, 1);
    removeFd(&sockets->write, s, 0);
  }

  return 0;
}
