fd_is_bash_input (fd)
     int fd;
{
  if (bash_input.type == st_bstream && bash_input.location.buffered_fd == fd)
    return 1;
  else if (interactive_shell == 0 && default_buffered_input == fd)
    return 1;
  return 0;
}
