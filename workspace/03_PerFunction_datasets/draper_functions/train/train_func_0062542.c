send_request(GIT_SOCKET s, const char *cmd, const char *url)
{
	int error;
	git_buf request = GIT_BUF_INIT;

	error = gen_proto(&request, cmd, url);
	if (error < 0)
		goto cleanup;

	error = gitno_send(s, request.ptr, request.size, 0);

cleanup:
	git_buf_free(&request);
	return error;
}
