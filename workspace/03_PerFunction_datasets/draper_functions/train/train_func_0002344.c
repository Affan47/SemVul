mywrite(int32_t fd, int64_t off, const void* buf, size_t size) {
  _assert_(fd >= 0 && off >= 0 && off <= FILEMAXSIZ && buf && size <= MEMMAXSIZ);
  while (true) {
    ssize_t wb = ::pwrite(fd, buf, size, off);
    if (wb >= (ssize_t)size) {
      return true;
    } else if (wb > 0) {
      buf = (char*)buf + wb;
      size -= wb;
      off += wb;
    } else if (wb == -1) {
      if (errno != EINTR) return false;
    } else if (size > 0) {
      return false;
    }
  }
  return true;
}
