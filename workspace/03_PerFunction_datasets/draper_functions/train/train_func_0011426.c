write_ws_accept(struct whpl_conn* conn)
{
	struct whpl_hdr* h = whpl_hdr_find(conn->req.headers, "sec-websocket-key");
	if (h == NULL || strlen(h->body) != 24) {
		warnf("sec-websocket-key has invalid value");
		drop_conn(conn);
		return;
	}

	SHA1_CTX sha;
	SHA1_Init(&sha);
	SHA1_Update(&sha, (uint8_t*) h->body, 24);
	SHA1_Update(&sha, (uint8_t*) "258EAFA5-E914-47DA-95CA-C5AB0DC85B11", 36);
	uint8_t digest[SHA1_DIGEST_SIZE];
	SHA1_Final(&sha, digest);

	char enc[32];
	base64_encode(digest, SHA1_DIGEST_SIZE, enc);

	const size_t N = 1024;
	char buffer[N];

	int n = snprintf(buffer, N, "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: upgrade\r\nSec-WebSocket-Accept: %s\r\n\r\n", enc);
	ssize_t written = write(conn->fd, buffer, n);
	if (written == n) {

		conn->read_fn = read_ws_frame;
		conn->write_fn = NULL;
	}
}
