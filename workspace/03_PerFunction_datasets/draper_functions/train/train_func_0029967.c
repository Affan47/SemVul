clear_parser_state(http_subtransport *t)
{
	unsigned i;
	char *entry;

	http_parser_init(&t->parser, HTTP_RESPONSE);
	gitno_buffer_setup(&t->socket,
		&t->parse_buffer,
		t->parse_buffer_data,
		sizeof(t->parse_buffer_data));

	t->last_cb = NONE;
	t->parse_error = 0;
	t->parse_finished = 0;

	git_buf_free(&t->parse_header_name);
	git_buf_init(&t->parse_header_name, 0);

	git_buf_free(&t->parse_header_value);
	git_buf_init(&t->parse_header_value, 0);

	git__free(t->content_type);
	t->content_type = NULL;

	git__free(t->location);
	t->location = NULL;

	git_vector_foreach(&t->www_authenticate, i, entry)
		git__free(entry);

	git_vector_free(&t->www_authenticate);
}
