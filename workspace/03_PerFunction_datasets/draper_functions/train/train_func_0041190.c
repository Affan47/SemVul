connection_free(struct connection *conn) {
  struct chunk *c, *next;

  if (conn->outevent.ev_events) {
    event_del(&conn->outevent);
  }

  if (conn->obsevent.ev_events) {
    event_del(&conn->obsevent);
  }

  close(conn->fd);
  close(conn->outfd);

  for (c = conn->outqhead; c; c = next) {
    next = c->next;
    free(c);
  }

  for (c = conn->obsqhead; c; c = next) {
    next = c->next;
    free(c);
  }

  obstcp_rbuf_free(&conn->rbuf);

  free(conn);
}
