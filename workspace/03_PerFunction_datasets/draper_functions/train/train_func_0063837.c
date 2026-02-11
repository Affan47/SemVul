dup_socket_channel(s48_call_t call, socket_t socket_fd)
{
  socket_t output_fd;
  s48_ref_t output_channel;
  int flags;

  RETRY_OR_RAISE_NEG(output_fd, dup(socket_fd));

  RETRY_OR_RAISE_NEG(flags, fcntl(output_fd, F_GETFL));
  flags |= O_NONBLOCK;
  RETRY_OR_RAISE_NEG(flags, fcntl(output_fd, F_SETFL, flags));

  output_channel = s48_add_channel_2(call, s48_channel_status_output_2(call),
				     s48_enter_string_latin_1_2(call, "socket connection"),
				     output_fd);

  if (!s48_channel_p_2(call, output_channel))
    {
      ps_close_fd(output_fd);
      s48_raise_scheme_exception_2(call, s48_extract_long_2(call, output_channel), 0);
    };

  return output_channel;
}
