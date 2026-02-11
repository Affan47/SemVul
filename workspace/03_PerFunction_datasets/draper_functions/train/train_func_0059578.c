_ircserver_connect2(struct ircproxy *p, void *data,
                                const char *ip, const char *host) {
  if (!host || !ip) {
    debug("DNS failure, retrying");
    timer_new((void *)p, "server_recon", p->conn_class->server_retry,
              TIMER_FUNCTION(_ircserver_reconnect), (void *)0);
    free(p->serverpassword);
    p->serverpassword = 0;
    return;
  }

  debug("Resolved server");


  free(p->servername);
  p->servername = x_strdup(host);
  net_filladdr(&p->server_addr, ip, (unsigned short)data);

  if (p->conn_class->local_address) {
    dns_addrfromhost((void *)p, 0, p->conn_class->local_address,
                     (dns_fun_t)_ircserver_connect3);
  } else {
    _ircserver_connect3(p, 0, 0, 0);
  }
}
