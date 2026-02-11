ptrace (enum __ptrace_request request, ...)
{
  va_list ap;
  pid_t pid;
  void *addr;
  void *data;

  va_start(ap, request);
  pid = va_arg(ap, pid_t);
  addr = va_arg(ap, void *);
  data = va_arg(ap, void *);
  va_end(ap);

  pid = dmtcp::VirtualPidTable::instance().originalToCurrentPid(pid);
  long ptrace_ret =  _real_ptrace(request, pid, addr, data);


  if (ptrace_ret == 0 && request == PTRACE_GETEVENTMSG) {
    unsigned long *ldata = (unsigned long*) data;
    *ldata = (unsigned long) currentToOriginalPid((pid_t) *ldata);
  }

  return ptrace_ret;
}
