l2tp_tunnel_genchall(uint16_t chall_len,
				struct l2tp_conn_t *conn,
				struct l2tp_packet_t *pack)
{
	void *ptr = NULL;
	int err;

	if (chall_len == 0
	    || conn->secret == NULL || conn->secret_len == 0) {
		if (conn->challenge) {
			_free(conn->challenge);
			conn->challenge = NULL;
		}
		conn->challenge_len = 0;
		return 0;
	}

	if (conn->challenge_len != chall_len) {
		ptr = _realloc(conn->challenge, chall_len);
		if (ptr == NULL) {
			log_tunnel(log_error, conn,
				   "impossible to generate Challenge:"
				   " memory allocation failed\n");
			goto err;
		}
		conn->challenge = ptr;
		conn->challenge_len = chall_len;
	}

	if (u_randbuf(conn->challenge, chall_len, &err) < 0) {
		if (err)
			log_tunnel(log_error, conn,
				   "impossible to generate Challenge:"
				   " reading from urandom failed: %s\n",
				   strerror(err));
		else
			log_tunnel(log_error, conn,
				   "impossible to generate Challenge:"
				   " end of file reached while reading"
				   " from urandom\n");
		goto err;
	}

	if (l2tp_packet_add_octets(pack, Challenge, conn->challenge,
				   conn->challenge_len, 1) < 0) {
		log_tunnel(log_error, conn,
			   "impossible to generate Challenge:"
			   " adding data to packet failed\n");
		goto err;
	}

	return 0;

err:
	if (conn->challenge) {
		_free(conn->challenge);
		conn->challenge = NULL;
	}
	conn->challenge_len = 0;
	return -1;
}
