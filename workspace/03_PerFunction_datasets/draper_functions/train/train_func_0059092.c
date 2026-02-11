send_to_one(conn_t *conn, const char *fmt, ...)
{
	int	ret;
	va_list	ap;
	char	buf[US_SOCK_BUF_LEN];

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	ret = write(conn->fd, buf, strlen(buf));

	if ((ret < 1) || (ret != (int) strlen(buf))) {
		upsdebugx(2, "write to fd %d failed", conn->fd);

		close(conn->fd);
		conn_del(conn);

		return 0;
	}

	return 1;
}
