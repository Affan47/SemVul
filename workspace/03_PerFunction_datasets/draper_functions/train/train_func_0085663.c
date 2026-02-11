proc_connection(void)
{
  fd_set rfds;
  fd_set wfds;
  int max_fd;
  int ret;

  max_fd = -1;
  FD_ZERO(&rfds);
  FD_ZERO(&wfds);
  if (daemon_sock >= 0) {
    max_fd = daemon_sock;
    FD_SET(daemon_sock, &rfds);
  }
  max_fd = MAX(conn->rfd, max_fd);
  FD_SET(conn->rfd, &rfds);
  if (conn->n_wbuf > 0) {
    max_fd = MAX(conn->wfd, max_fd);
    FD_SET(conn->wfd, &wfds);
  }

  if (max_fd == -1)
    return -1;

  ret = select(max_fd + 1, &rfds, &wfds, NULL, NULL);
  if (ret < 0) {
    return -1;
  }

  if (conn->n_wbuf > 0 && FD_ISSET(conn->wfd, &wfds)) {
    ret = write(conn->wfd, conn->wbuf, conn->n_wbuf);
    if (ret <= 0) {
      kill_connection (conn);
    } else {
      conn->n_wbuf -= ret;
      if (conn->n_wbuf > 0) {
	memmove(conn->wbuf, conn->wbuf + ret, conn->n_wbuf);
      }
    }
  }

  if (FD_ISSET(conn->rfd, &rfds)) {
    ensure_buffer(&conn->rbuf, &conn->s_rbuf,
		  conn->n_rbuf + BUF_GROW_SIZE);
    ret = read(conn->rfd,
	       conn->rbuf + conn->n_rbuf, conn->s_rbuf - conn->n_rbuf);
    if (ret <= 0) {
      kill_connection (conn);
    } else {
      conn->n_rbuf += ret;
    }
  }
  return 0;
}
