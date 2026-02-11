connection_out_cb(int fd, short events, void *arg) {
  struct connection *conn = (struct connection *) arg;

  if (EV_READ & events) {
    int queued;
    if (ioctl(conn->outfd, SIOCINQ, &queued)) {
      perror("ioctl");
      connection_free(conn);
      return;
    }
    if (!queued) queued = 16;

    struct chunk *c = malloc(sizeof(struct chunk) + queued + CHUNK_OVERHEAD);
    if (!c) return;
    memset(c, 0, sizeof(struct chunk));
    c->done = CHUNK_PRE;

    ssize_t n;
    do {
      n = read(conn->outfd, c->data + CHUNK_PRE, queued);
    } while (n == -1 && errno == EINTR);

    if (n < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return;
      perror("read");
      free(c);
      connection_free(conn);
      return;
    } else if (n == 0) {
      free(c);
      connection_free(conn);
      return;
    } else {
      c->length = n + c->done;
      const char was_empty_q = conn->obsqhead ? 0 : 1;

      connection_obs_prepare(conn, c);
      chunk_nq(c, &conn->obsqhead, &conn->obsqtail);
      conn->obsqlen += c->length;

      if (was_empty_q) connection_obs_write(conn);
    }
  }

  if (EV_WRITE & events) {
    if (!connection_out_write(conn)) return;
  }

  connection_setevents(conn);
}
