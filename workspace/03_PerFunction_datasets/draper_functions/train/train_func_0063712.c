local_connect(git_transport *transport, int GIT_UNUSED(direction))
{
	git_repository *repo;
	int error;
	transport_local *t = (transport_local *) transport;
	const char *path;
	const char file_prefix[] = "file://";
	GIT_UNUSED_ARG(direction);


	if (!git__prefixcmp(transport->url, file_prefix))
		path = transport->url + STRLEN(file_prefix);
	else
		path = transport->url;

	error = git_repository_open(&repo, path);
	if (error < GIT_SUCCESS)
		return git__rethrow(error, "Failed to open remote");

	t->repo = repo;
	t->parent.connected = 1;

	return GIT_SUCCESS;
}
