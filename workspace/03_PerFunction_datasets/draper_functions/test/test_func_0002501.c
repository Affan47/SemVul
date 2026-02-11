send(const void* buf, size_t size) {
  _assert_(buf && size <= kc::MEMMAXSIZ);
  SocketCore* core = (SocketCore*)opq_;
  if (core->fd < 1) {
    sockseterrmsg(core, "not opened");
    return false;
  }
  const char* rp = (const char*)buf;
  double ct = kc::time();
  while (size > 0) {
    int32_t wb = ::send(core->fd, rp, size, 0);
    switch (wb) {
      case -1: {
        if (!checkerrnoretriable(errno)) {
          sockseterrmsg(core, "send failed");
          return false;
        }
        if (kc::time() > ct + core->timeout) {
          sockseterrmsg(core, "operation timed out");
          return false;
        }
        if (core->aborted) {
          sockseterrmsg(core, "operation was aborted");
          return false;
        }
        if (!waitsocket(core->fd, 1, WAITTIME)) {
          sockseterrmsg(core, "waitsocket failed");
          return false;
        }
        break;
      }
      case 0: {
        break;
      }
      default: {
        rp += wb;
        size -= wb;
        break;
      }
    }
  }
  return true;
}
