s48_listen(s48_call_t call, s48_ref_t sch_channel, s48_ref_t sch_queue_size)
{
  socket_t socket_fd = s48_extract_socket_fd(call, sch_channel);
  int queue_size = s48_extract_long_2(call, sch_queue_size);
  int status;

  RETRY_OR_RAISE_NEG(status, listen(socket_fd, queue_size));

  return s48_unspecific_2(call);
}
