sigpause(int sig)
{
  JWARNING(false)
    .Text("This function is deprecated. Use sigsuspend instead." \
          "  The DMTCP wrappers for this function may not be fully tested");
  return _real_sigpause(sig);
}
