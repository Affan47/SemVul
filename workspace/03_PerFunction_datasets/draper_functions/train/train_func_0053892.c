wait_for_client_kill(Sock *sock, int sig)
{
  int ret_val;
  switch(sock->purpose) {
  case SessionManager:
  case ViewportServer:
    sock_accept_connection(sock->purpose);
    ret_val = send_signal(purpose_table[sock->purpose], sig);
    sock->socket = 0;
    return ret_val;
  default:
    sock->socket = 0;
    return -1;
  }
}
