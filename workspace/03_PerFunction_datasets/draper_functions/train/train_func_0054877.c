nonFatalError()
{
  int err = XmlRpcSocket::getError();
  return (err == EINPROGRESS ||
#if defined(EAGAIN)
          err == EAGAIN ||
#endif
#if defined(EINTR)
          err == EINTR ||
#endif
          err == EWOULDBLOCK);
}
