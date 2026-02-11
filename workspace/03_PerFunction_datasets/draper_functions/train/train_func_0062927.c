read_http(struct whpl_conn* conn)
{
	char* buf = conn->read_buffer + conn->read_buffer_top;
	size_t nmax = READ_BUFFER_SIZE - conn->read_buffer_top;
	ssize_t n = read(conn->fd, buf, nmax);
	if (n > 0) {
		conn->read_buffer_top += n;
		parse_http(conn, buf, n);
		if (conn->hp.err) {
			dbgf("http parser error, dropping connection");
			drop_conn(conn);
		} else if (conn->hp.where != HP_BODY && conn->read_buffer_top == READ_BUFFER_SIZE) {

			dbgf("ARGH -- read http request header until top (%d)", READ_BUFFER_SIZE);
			dbgf("and still found no body; dropping connection,");
			dbgf("but ought to throw a 413 or 414 for good meassure");

			drop_conn(conn);
		} else if (conn->hp.where == HP_BODY) {
			on_body(conn);
		}
	} else if (n == 0) {
		dbgf("(connection lost)");
		drop_conn(conn);
	} else {
		if (errno == EAGAIN) return;
		perror("read");
		exit(1);
	}
}
