_ircserver_connectfailed(struct ircproxy *p, int sock, int bad) {
  if (sock != p->server_sock) {
    error("Unexpected socket %d in _ircserver_connectfailed, expected %d", sock,
          p->server_sock);
    net_close(&sock);
    return;
  }

  debug("Connection failed");

  if (IS_CLIENT_READY(p))
    ircclient_send_notice(p, "Connection failed: %s", strerror(errno));

  net_close(&(p->server_sock));
  p->server_status &= ~(IRC_SERVER_CREATED);

  timer_new((void *)p, "server_recon", p->conn_class->server_retry,
            TIMER_FUNCTION(_ircserver_reconnect), (void *)0);
}
