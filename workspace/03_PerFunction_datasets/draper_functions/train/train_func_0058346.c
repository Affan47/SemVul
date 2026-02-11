vopen_fd_from_path(int flags, int mode, const char* logkey, int reperr, const char* name_fmt, va_list ap)
{
  fdtype fd;
  char buf[ZXID_MAX_BUF];
  DD("vopen_fd_from_path(%d, %d, %s, %d, %s)", flags, mode, logkey, reperr, name_fmt);
  if (!vname_from_path(buf, sizeof(buf), name_fmt, ap))
    return BADFD;
#ifdef MINGW
  if (flags == O_RDONLY) {
    fd = openfile_ro(buf);
  } else {
    fd = zx_CreateFile(buf, MINGW_RW_PERM, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  }
#else
  fd = open(buf, flags, mode);
#endif
  if (fd == BADFD) {
    if (reperr && logkey[0] != '-') {
      perror("open (vopen_fd_from_path)");
      ERR("File(%s) not found lk(%s) errno=%d err(%s). flags=0x%x, euid=%d egid=%d", buf, logkey, errno, STRERROR(errno), flags, geteuid(), getegid());
    } else {
      D("File(%s) not found lk(%s) errno=%d err(%s). flags=0x%x, euid=%d egid=%d", buf, logkey, errno, STRERROR(errno), flags, geteuid(), getegid());
    }
    return BADFD;
  }
  return fd;
}
