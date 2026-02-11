dual_tls_send(rad_listen_t *listener, REQUEST *request)
{
	listen_socket_t *sock = listener->data;

	rad_assert(request->listener == listener);
	rad_assert(listener->send == dual_tls_send);


	if (request->reply->code == 0) return 0;


	if (rad_encode(request->reply, request->packet,
		       request->client->secret) < 0) {
		RDEBUG("Failed encoding packet: %s", fr_strerror());
		return 0;
	}


	if (rad_sign(request->reply, request->packet,
		       request->client->secret) < 0) {
		RDEBUG("Failed signing packet: %s", fr_strerror());
		return 0;
	}

	PTHREAD_MUTEX_LOCK(&sock->mutex);


	record_plus(&sock->ssn->clean_in,
		    request->reply->data, request->reply->data_len);


	tls_handshake_send(request, sock->ssn);


	if (sock->ssn->dirty_out.used > 0) {
		dump_hex("WRITE TO SSL", sock->ssn->dirty_out.data, sock->ssn->dirty_out.used);

		tls_socket_write(listener, request);
	}
	PTHREAD_MUTEX_UNLOCK(&sock->mutex);

	return 0;
}
