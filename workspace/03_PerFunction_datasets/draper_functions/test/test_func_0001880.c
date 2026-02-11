dlopen(const char *filename, int flag)
{
  void *ret;
  WRAPPER_EXECUTION_DISABLE_CKPT();
  dmtcp::ThreadSync::setThreadPerformingDlopenDlsym();
  ret = _real_dlopen(filename, flag);

  dmtcp::ThreadSync::unsetThreadPerformingDlopenDlsym();
  WRAPPER_EXECUTION_ENABLE_CKPT();
  return ret;
}
