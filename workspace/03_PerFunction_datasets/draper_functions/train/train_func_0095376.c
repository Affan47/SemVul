read_socket_data(int sock, struct socket_packet_buffer *buffer)
{
  int didget;

  if (!buffer_ensure_free_extra_space(buffer, MAX_LEN_PACKET)) {
    log_error("can't grow buffer");
    return -1;
  }

  log_debug("try reading %d bytes", buffer->nsize - buffer->ndata);
  didget = fc_readsocket(sock, (char *) (buffer->data + buffer->ndata),
			 buffer->nsize - buffer->ndata);

  if (didget > 0) {
    buffer->ndata+=didget;
    log_debug("didget:%d", didget);
    return didget;
  }
  else if (didget == 0) {
    log_debug("EOF on socket read");
    return -2;
  }
#ifdef NONBLOCKING_SOCKETS
  else if (errno == EWOULDBLOCK || errno == EAGAIN) {
    log_debug("EGAIN on socket read");
    return 0;
  }
#endif
  return -1;
}
