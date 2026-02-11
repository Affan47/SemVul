read(char *buf, size_t bufSize, Messenger &mgr,
				   size_t &nread)
{
  if (readSaved(buf, bufSize, nread))
    return 1;
  if (fd_ < 0 || eof_)
    return 0;
  long n;
  do {
    n = ::read(fd_, buf, bufSize);
  } while (n < 0 && errno == EINTR);
  if (n > 0) {
    nread = size_t(n);
    saveBytes(buf, nread);
    return 1;
  }
  if (n < 0) {
    ParentLocationMessenger(mgr).message(PosixStorageMessages::fdRead,
					 NumberMessageArg(fd_),
					 ErrnoMessageArg(errno));
    fd_ = -1;
  }
  else
    eof_ = 1;
  return 0;
}
