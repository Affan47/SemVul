s48_extract_socket_fd(s48_call_t call, s48_ref_t sch_channel)
{
  s48_check_channel_2(call, sch_channel);
  return s48_extract_long_2(call, s48_unsafe_channel_os_index_2(call, sch_channel));
}
