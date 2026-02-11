http_close(git_smart_subtransport *subtransport)
{
	http_subtransport *t = (http_subtransport *) subtransport;
	git_http_auth_context *context;
	size_t i;

	clear_parser_state(t);

	if (t->socket.socket) {
		gitno_close(&t->socket);
		memset(&t->socket, 0x0, sizeof(gitno_socket));
	}

	if (t->cred) {
		t->cred->free(t->cred);
		t->cred = NULL;
	}

	if (t->url_cred) {
		t->url_cred->free(t->url_cred);
		t->url_cred = NULL;
	}

	git_vector_foreach(&t->auth_contexts, i, context) {
		if (context->free)
			context->free(context);
	}

	git_vector_clear(&t->auth_contexts);

	gitno_connection_data_free_ptrs(&t->connection_data);

	return 0;
}
