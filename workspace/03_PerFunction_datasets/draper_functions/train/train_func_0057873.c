ircclient_send_error(struct ircproxy *p, const char *format, ...) {
  char *msg, *nick, *user, *host;
  va_list ap;
  int ret;

  va_start(ap, format);
  msg = x_vsprintf(format, ap);
  va_end(ap);

  nick = p->nickname ? p->nickname : "";
  user = p->username ? p->username : "user";
  host = p->hostname ? p->hostname : "host";

  ret = net_send(p->client_sock, "%s :%s: %s[%s@%s] (%s)\r\n",
                 "ERROR", "Closing Link", nick, user, host, msg);
  debug("<- '%s :%s: %s[%s@%s] (%s)'", "ERROR", "Closing Link",
        nick, user, host, msg);

  free(msg);
  return ret;
}
