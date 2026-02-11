evhttp_dispatch_callback(struct httpcbq *callbacks, struct evhttp_request *req)
{
	struct evhttp_cb *cb;
	size_t offset = 0;
	char *translated;
	const char *path;


	path = evhttp_uri_get_path(req->uri_elems);
	offset = strlen(path);
	if ((translated = mm_malloc(offset + 1)) == NULL)
		return (NULL);
	evhttp_decode_uri_internal(path, offset, translated,
	    0 );

	TAILQ_FOREACH(cb, callbacks, next) {
		if (!strcmp(cb->what, translated)) {
			mm_free(translated);
			return (cb);
		}
	}

	mm_free(translated);
	return (NULL);
}
