s48_socket(s48_call_t call, s48_ref_t sch_af, s48_ref_t sch_type, s48_ref_t sch_protocol)
{
  socket_t fd;
  int mode, status;
  s48_ref_t sch_channel;
  int af = s48_extract_af(call, sch_af);
  int socktype = s48_extract_socket_type(call, sch_type);
  int protocol = s48_extract_long_2(call, sch_protocol);

  RETRY_OR_RAISE_NEG(fd, socket(af, socktype, protocol));
  RETRY_OR_RAISE_NEG(status, fcntl(fd, F_SETFL, O_NONBLOCK));

  sch_channel = s48_add_channel_2(call, s48_channel_status_special_input_2(call),
				  s48_enter_string_latin_1_2(call, "socket"), fd);

  if (!s48_channel_p_2(call, sch_channel))
    {
      ps_close_fd(fd);
      s48_raise_scheme_exception_2(call, s48_extract_long_2(call, sch_channel), 0);
    }

  return sch_channel;
}
