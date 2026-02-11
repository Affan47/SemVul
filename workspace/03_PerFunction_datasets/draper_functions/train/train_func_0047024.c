conn_mod_read_cb(rb_fde_t *fd, void *data)
{
	conn_t *conn = data;
	const char *err = remote_closed;
	int length;
	if(conn == NULL)
		return;
	if(IsDead(conn))
		return;

	if(IsSSLRWantsW(conn))
	{
		ClearSSLRWantsW(conn);
		conn_mod_write_sendq(conn->mod_fd, conn);
		if(IsDead(conn))
			return;
	}

	while(1)
	{
		if(IsDead(conn))
			return;

		length = rb_read(conn->mod_fd, inbuf, sizeof(inbuf));

		if(length == 0 || (length < 0 && !rb_ignore_errno(errno)))
		{
			if(length == 0)
			{
				close_conn(conn, WAIT_PLAIN, "%s", remote_closed);
				return;
			}

			if(IsSSL(conn) && length == RB_RW_SSL_ERROR)
				err = rb_get_ssl_strerror(conn->mod_fd);
			else
				err = strerror(errno);
			close_conn(conn, WAIT_PLAIN, "Read error: %s", err);
			return;
		}
		if(length < 0)
		{
			if(length != RB_RW_SSL_NEED_WRITE)
				rb_setselect(conn->mod_fd, RB_SELECT_READ, conn_mod_read_cb, conn);
			else
			{
				rb_setselect(conn->mod_fd, RB_SELECT_READ, NULL, NULL);
				rb_setselect(conn->mod_fd, RB_SELECT_WRITE, conn_mod_read_cb, conn);
				SetSSLRWantsW(conn);
			}
			conn_plain_write_sendq(conn->plain_fd, conn);
			return;
		}
		conn->mod_in += length;
#ifdef HAVE_LIBZ
		if(IsZip(conn))
			common_zlib_inflate(conn, inbuf, length);
		else
#endif
			conn_plain_write(conn, inbuf, length);
	}
}
