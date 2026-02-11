ssh_flush_termination(void *c){
  ssh_session session = c;
  if (ssh_socket_buffered_write_bytes(session->socket) == 0 ||
      session->session_state == SSH_SESSION_STATE_ERROR)
    return 1;
  else
    return 0;
}
