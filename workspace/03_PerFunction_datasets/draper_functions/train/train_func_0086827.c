unix_sigpending(value unit)
{
  sigset_t pending;
  if (sigpending(&pending) == -1) uerror("sigpending", Nothing);
  return encode_sigset(&pending);
}
