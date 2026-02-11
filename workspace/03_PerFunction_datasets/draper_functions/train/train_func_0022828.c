OnClose(talk_base::AsyncPacketSocket* socket, int error) {
  ASSERT(socket == socket_);
  LOG_J(LS_VERBOSE, this) << "Connection closed with error " << error;
  set_connected(false);
  set_write_state(STATE_WRITE_TIMEOUT);
}
