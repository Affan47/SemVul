raw_sock_to_buf(struct connection *conn, struct buffer *buf, int count)
{
	int ret, done = 0;
	int try;

	if (!conn_ctrl_ready(conn))
		return 0;

	if (!fd_recv_ready(conn->t.sock.fd))
		return 0;

	errno = 0;

	if (unlikely(!(fdtab[conn->t.sock.fd].ev & FD_POLL_IN))) {

		if ((fdtab[conn->t.sock.fd].ev & (FD_POLL_ERR|FD_POLL_HUP)) == FD_POLL_HUP)
			goto read0;


		if ((fdtab[conn->t.sock.fd].ev & FD_POLL_ERR) && (conn->flags & CO_FL_WAIT_L4_CONN)) {
			conn->flags |= CO_FL_ERROR | CO_FL_SOCK_RD_SH | CO_FL_SOCK_WR_SH;
			return done;
		}
	}


	if (buffer_empty(buf))
		buf->p = buf->data;


	while (count > 0) {

		try = buf->data + buf->size - (buf->p + buf->i);

		if (try <= 0) {
			try = buf->p - (buf->data + buf->o);
			if (try <= 0)
				break;
		}
		if (try > count)
			try = count;

		ret = recv(conn->t.sock.fd, bi_end(buf), try, 0);

		if (ret > 0) {
			buf->i += ret;
			done += ret;
			if (ret < try) {


				if (fdtab[conn->t.sock.fd].ev & FD_POLL_HUP)
					goto read0;

				fd_done_recv(conn->t.sock.fd);
				break;
			}
			count -= ret;
		}
		else if (ret == 0) {
			goto read0;
		}
		else if (errno == EAGAIN || errno == ENOTCONN) {
			fd_cant_recv(conn->t.sock.fd);
			break;
		}
		else if (errno != EINTR) {
			conn->flags |= CO_FL_ERROR | CO_FL_SOCK_RD_SH | CO_FL_SOCK_WR_SH;
			break;
		}
	}

	if (unlikely(conn->flags & CO_FL_WAIT_L4_CONN) && done)
		conn->flags &= ~CO_FL_WAIT_L4_CONN;
	return done;

 read0:
	conn_sock_read0(conn);
	conn->flags &= ~CO_FL_WAIT_L4_CONN;


	if (unlikely(fdtab[conn->t.sock.fd].ev & FD_POLL_ERR))
		conn->flags |= CO_FL_ERROR | CO_FL_SOCK_RD_SH | CO_FL_SOCK_WR_SH;
	return done;
}
