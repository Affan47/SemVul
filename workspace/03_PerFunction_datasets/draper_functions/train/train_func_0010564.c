doLocking(const dmtcp::vector<int>& fds)
{
  if (dmtcp::Util::strStartsWith(_path, "/proc/")) {
    int index = 6;
    char *rest;
    pid_t proc_pid = strtol(&_path[index], &rest, 0);
    if (proc_pid > 0 && *rest == '/') {
      _type = FILE_PROCFS;
      if (proc_pid != getpid()) {
        return;
      }
    }
  }
  Connection::doLocking(fds);
}
