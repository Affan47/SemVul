transport_find_fn(const char *url, git_transport_cb *callback, void **param)
{
	size_t i = 0;
	unsigned priority = 0;
	transport_definition *definition = NULL, *definition_iter;


	for (i = 0; i < GIT_TRANSPORT_COUNT; ++i) {
		definition_iter = &transports[i];

		if (strncasecmp(url, definition_iter->prefix, strlen(definition_iter->prefix)))
			continue;

		if (definition_iter->priority > priority)
			definition = definition_iter;
	}

#ifdef GIT_WIN32


	if (!definition && git_path_exists(url) && git_path_isdir(url))
		definition = &local_transport_definition;


	if (!definition && strrchr(url, ':'))
		definition = &dummy_transport_definition;
#else


	if (!definition && strrchr(url, ':'))
#ifdef GIT_SSH
		definition = &ssh_transport_definition;
#else
        definition = &dummy_transport_definition;
#endif


	if (!definition && git_path_exists(url) && git_path_isdir(url))
		definition = &local_transport_definition;
#endif

	if (!definition)
		return -1;

	*callback = definition->fn;
	*param = definition->param;

	return 0;
}
