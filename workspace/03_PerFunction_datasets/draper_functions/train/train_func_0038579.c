tcpaccept(int socket, _addr *askaddr) {
  _addr querier;
  socklen_t len = sizeof(_addr);
  int ret = accept(socket, (sockaddr *)&querier, &len);
  if (ret < 0) throw PException("Could not accept TCP connection");
  if (askaddr) memcpy(askaddr, &querier, len);
  return ret;
}
