tcp_server_start (struct tcp_server *ts)
{
  struct sockaddr_in addr;
  int len = sizeof(struct sockaddr_in);
  int state = 1;
  int ret;

  ts->sock = socket (AF_INET, SOCK_STREAM, 0);
  if (ts->sock < 0)
    {
      logger_err (ts->reg->lg, "TCP Server: socket() error: %s",
                  strerror (errno));
      return -1;
    }

  memset (&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
#ifdef HAVE_SIN_LEN
  addr.sin_len = len;
#endif
  addr.sin_port = htons (ts->port);
  addr.sin_addr = ts->addr;


  if (bind (ts->sock, (struct sockaddr *)&addr, len) < 0)
    {
      logger_err (ts->reg->lg, "TCP Server: bind() error: %s",
                  strerror (errno));
      close (ts->sock);
      ts->sock = -1;
      return -1;
    }


  if (listen (ts->sock, ts->backlog) < 0)
    {
      logger_err (ts->reg->lg, "TCP Server: listen() error: %s",
                  strerror (errno));
      close (ts->sock);
      ts->sock = -1;
      return -1;
    }

  ts->e_accept = event_master_add_read (ts->reg->em, NULL,
                                        tcp_server_accept, ts, ts->sock);

  return 0;
}
