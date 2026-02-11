git_stream_alloc(
	git_subtransport *t,
	const char *url,
	const char *cmd,
	git_smart_subtransport_stream **stream)
{
	git_stream *s;

	if (!stream)
		return -1;

	s = git__calloc(sizeof(git_stream), 1);
	GITERR_CHECK_ALLOC(s);

	s->parent.subtransport = &t->parent;
	s->parent.read = git_stream_read;
	s->parent.write = git_stream_write;
	s->parent.free = git_stream_free;

	s->cmd = cmd;
	s->url = git__strdup(url);

	if (!s->url) {
		git__free(s);
		return -1;
	}

	*stream = &s->parent;
	return 0;
}
