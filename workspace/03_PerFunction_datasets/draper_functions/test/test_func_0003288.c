sock_read(conn_t *conn)
{
	int	i, ret;
	char	ch;

	for (i = 0; i < US_MAX_READ; i++) {

		ret = read(conn->fd, &ch, 1);

		if (ret < 1) {


			if ((ret == -1) && (errno == EAGAIN))
				return 0;


			return -1;
		}

		ret = pconf_char(&conn->ctx, ch);

		if (ret == 0)
			continue;

		if (ret == -1) {
			upslogx(LOG_NOTICE, "Parse error on sock: %s",
				conn->ctx.errmsg);

			return 0;
		}


		if (!sock_arg(conn)) {
			log_unknown(conn->ctx.numargs, conn->ctx.arglist);
			send_to_one(conn, "ERR UNKNOWN\n");
		}

		return 1;
	}

	return 0;
}
