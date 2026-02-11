ns_server_wakeup(struct ns_server *server) {
  unsigned char ch = 0;
  if (server->ctl[0] != INVALID_SOCKET) {
    send(server->ctl[0], &ch, 1, 0);
    recv(server->ctl[0], &ch, 1, 0);
  }
}
