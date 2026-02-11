GetSockName(const Arguments& args) {
  HandleScope scope;

  FD_ARG(args[0])

  struct sockaddr_storage address_storage;
  socklen_t len = sizeof(struct sockaddr_storage);

#ifdef __POSIX__
  if (0 > getsockname(fd, (struct sockaddr *) &address_storage, &len)) {
    return ThrowException(ErrnoException(errno, "getsockname"));
  }

#else
  if (SOCKET_ERROR == getsockname(_get_osfhandle(fd),
      (struct sockaddr *) &address_storage, &len)) {
    return ThrowException(ErrnoException(WSAGetLastError(), "getsockname"));
  }
#endif

  Local<Object> info = Object::New();
  ADDRESS_TO_JS(info, address_storage, len);
  return scope.Close(info);
}
