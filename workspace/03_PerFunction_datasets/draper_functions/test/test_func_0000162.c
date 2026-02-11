s48_socketpair(s48_call_t call, s48_ref_t sch_af, s48_ref_t sch_type, s48_ref_t sch_protocol)
{
  int status;
  s48_ref_t sch_channel0, sch_channel1;
  s48_ref_t sch_result;
  int af = s48_extract_af(call, sch_af);
  int socktype = s48_extract_socket_type(call, sch_type);
  int protocol = s48_extract_long_2(call, sch_protocol);
  socket_t fds[2];

  RETRY_OR_RAISE_NEG(status, socketpair(af, socktype, protocol, fds));

  RETRY_OR_RAISE_NEG(status, fcntl(fds[0], F_SETFL, O_NONBLOCK));
  RETRY_OR_RAISE_NEG(status, fcntl(fds[1], F_SETFL, O_NONBLOCK));

  sch_channel0 = s48_add_channel_2(call, s48_channel_status_input_2(call),
				   s48_enter_string_latin_1_2(call, "socket"), fds[0]);
  sch_channel1 = s48_add_channel_2(call, s48_channel_status_input_2(call),
				   s48_enter_string_latin_1_2(call, "socket"), fds[1]);


  sch_result = s48_cons_2(call, sch_channel0, sch_channel1);
  return sch_result;
}
