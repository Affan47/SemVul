tcpsend(int socket, const char *buff, int bufflen) {
  int ret = send(socket, buff, bufflen, 0);
  if (ret < 0 && errno != EAGAIN) throw PException("Could not send TCP message");
  return ret;
}
