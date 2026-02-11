git_transport_new(git_transport **out, const char *url)
{
	git_transport_cb fn;
	git_transport *transport;
	int error;

	fn = transport_new_fn(url);

	error = fn(&transport);
	if (error < GIT_SUCCESS)
		return git__rethrow(error, "Failed to create new transport");

	transport->url = git__strdup(url);
	if (transport->url == NULL)
		return GIT_ENOMEM;

	*out = transport;

	return GIT_SUCCESS;
}
