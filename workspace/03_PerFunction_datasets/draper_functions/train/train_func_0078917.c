caml_channel_size(struct channel *channel)
{
  file_offset offset;
  file_offset end;
  int fd;


  fd = channel->fd;
  offset = channel->offset;
  caml_enter_blocking_section();
  end = lseek(fd, 0, SEEK_END);
  if (end == -1 || lseek(fd, offset, SEEK_SET) != offset) {
    caml_leave_blocking_section();
    caml_sys_error(NO_ARG);
  }
  caml_leave_blocking_section();
  return end;
}
