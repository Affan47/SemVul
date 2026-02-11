caml_channel_descriptor(value vchannel)
{
  int fd = Channel(vchannel)->fd;
  if (fd == -1) { errno = EBADF; caml_sys_error(NO_ARG); }
  return Val_int(fd);
}
