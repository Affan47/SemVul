receive_line(void* buf, size_t max) {
  _assert_(buf && max > 0 && max <= kc::MEMMAXSIZ);
  SocketCore* core = (SocketCore*)opq_;
  if (core->fd < 1) {
    sockseterrmsg(core, "not opened");
    return false;
  }
  bool err = false;
  char* wp = (char*)buf;
  while (max > 1) {
    int32_t c = sockgetc(core);
    if (c == '\n') break;
    if (c < 0) {
      err = true;
      break;
    }
    if (c != '\r') {
      *(wp++) = c;
      max--;
    }
  }
  *wp = '\0';
  return !err;
}
