caml_seek_out(struct channel *channel, file_offset dest)
{
  caml_flush(channel);
  caml_enter_blocking_section();
  if (lseek(channel->fd, dest, SEEK_SET) != dest) {
    caml_leave_blocking_section();
    caml_sys_error(NO_ARG);
  }
  caml_leave_blocking_section();
  channel->offset = dest;
}
