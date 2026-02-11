httpc_seek(http_session_t * session, long long offset, int whence) {

	if (session->type != HTTPC_SESSION_NORMAL)
		return -1;

#ifdef HTTPC_DEBUG
	printf("[HTTPC_SEEK] offset = %lld  whence = %d  byte_pos = %lld\n",
	       offset, whence, session->byte_pos);
#endif
	switch (whence) {
	case SEEK_SET:
		if (offset == session->byte_pos) {
#ifdef HTTPC_DEBUG
			printf("noop SEEK_SET\n");
#endif
			return session->byte_pos;
		}
		break;
	case SEEK_CUR:
		if (offset == 0) {
#ifdef HTTPC_DEBUG
			printf("noop SEEK_CUR\n");
#endif
			return session->byte_pos;
		}
		break;
	case SEEK_END:
		if (session->headers.content_length - offset == session->byte_pos) {
#ifdef HTTPC_DEBUG
			printf("noop SEEK_END\n");
#endif
			return session->byte_pos;
		}
		break;
	}

	if (session->is_active) {
#ifdef HTTPC_DEBUG
		printf("[HTTPC] Closing stream\n");
#endif
		httpc_close(session);
	}

	switch (whence) {
	case SEEK_SET:
#ifdef HTTPC_DEBUG
		printf("[HTTPC] SEEK_SET offset = %lld\n", offset);
#endif
		if (offset > session->headers.content_length) {
			offset = session->headers.content_length;
		}
		session->byte_pos = offset;
		break;
	case SEEK_CUR:
#ifdef HTTPC_DEBUG
		printf("[HTTPC] SEEK_CUR offset = %lld\n", offset);
#endif
		if (offset + session->byte_pos > session->headers.content_length) {
			session->byte_pos = session->headers.content_length;
		} else {
			session->byte_pos += offset;
		}
		break;
	case SEEK_END:
#ifdef HTTPC_DEBUG
		printf("[HTTPC] SEEK_END offset = %lld\n", offset);
#endif
		if (offset > session->headers.content_length - session->byte_pos) {
			session->byte_pos = 0L;
		} else {
			session->byte_pos = session->headers.content_length - offset;
		}
		break;
	}

	return session->byte_pos;
}
