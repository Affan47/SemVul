gen_request(
	git_buf *buf,
	http_stream *s,
	size_t content_length)
{
	http_subtransport *t = OWNING_SUBTRANSPORT(s);

	if (!t->path)
		t->path = "/";


	if (s->redirect_url)
		git_buf_printf(buf, "%s %s HTTP/1.1\r\n", s->verb, s->redirect_url);
	else
		git_buf_printf(buf, "%s %s%s HTTP/1.1\r\n", s->verb, t->path, s->service_url);

	git_buf_puts(buf, "User-Agent: git/1.0 (libgit2 " LIBGIT2_VERSION ")\r\n");
	git_buf_printf(buf, "Host: %s\r\n", t->host);

	if (s->chunked || content_length > 0) {
		git_buf_printf(buf, "Accept: application/x-git-%s-result\r\n", s->service);
		git_buf_printf(buf, "Content-Type: application/x-git-%s-request\r\n", s->service);

		if (s->chunked)
			git_buf_puts(buf, "Transfer-Encoding: chunked\r\n");
		else
			git_buf_printf(buf, "Content-Length: %"PRIuZ "\r\n", content_length);
	} else
		git_buf_puts(buf, "Accept: */*\r\n");


	if (t->cred && t->cred->credtype == GIT_CREDTYPE_USERPASS_PLAINTEXT &&
		t->auth_mechanism == GIT_HTTP_AUTH_BASIC &&
		apply_basic_credential(buf, t->cred) < 0)
		return -1;


	if (!t->cred && t->user_from_url && t->pass_from_url) {
		if (!t->url_cred &&
			 git_cred_userpass_plaintext_new(&t->url_cred, t->user_from_url, t->pass_from_url) < 0)
			return -1;
		if (apply_basic_credential(buf, t->url_cred) < 0) return -1;
	}

	git_buf_puts(buf, "\r\n");

	if (git_buf_oom(buf))
		return -1;

	return 0;
}
