writeProcMaps() {
  char mapsBuf[50000];
  int  count;
  int fd = jalib::open("/proc/self/maps", O_RDONLY, 0);
  if (fd == -1) return;
  count = jalib::readAll(fd, mapsBuf, sizeof(mapsBuf) - 1);
  close(fd);

  dmtcp::ostringstream o;
  o << jalib::dmtcp_get_tmpdir() << "/proc-maps."
    << jalib::dmtcp_get_uniquepid_str();
  fd = open(o.str().c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR);
  if (fd == -1) return;
  count = jalib::writeAll(fd, mapsBuf, count);
  close(fd);
}
