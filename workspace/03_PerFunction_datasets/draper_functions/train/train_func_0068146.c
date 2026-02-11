ast_channel_iterator_by_exten_new(const char *exten, const char *context)
{
	struct ast_channel_iterator *i;
	char *l_exten = (char *) exten;
	char *l_context = (char *) context;

	if (!(i = ast_calloc(1, sizeof(*i)))) {
		return NULL;
	}

	i->active_iterator = (void *) ast_channel_callback(ast_channel_by_exten_cb,
		l_context, l_exten, OBJ_MULTIPLE);
	if (!i->active_iterator) {
		ast_free(i);
		return NULL;
	}

	return i;
}
