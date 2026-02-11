basic_next_token(
	git_buf *out, git_http_auth_context *ctx, git_cred *c)
{
	git_cred_userpass_plaintext *cred;
	git_buf raw = GIT_BUF_INIT;
	int error = -1;

	GIT_UNUSED(ctx);

	if (c->credtype != GIT_CREDTYPE_USERPASS_PLAINTEXT) {
		giterr_set(GITERR_INVALID, "invalid credential type for basic auth");
		goto on_error;
	}

	cred = (git_cred_userpass_plaintext *)c;

	git_buf_printf(&raw, "%s:%s", cred->username, cred->password);

	if (git_buf_oom(&raw) ||
		git_buf_puts(out, "Authorization: Basic ") < 0 ||
		git_buf_encode_base64(out, git_buf_cstr(&raw), raw.size) < 0 ||
		git_buf_puts(out, "\r\n") < 0)
		goto on_error;

	error = 0;

on_error:
	if (raw.size)
		git__memzero(raw.ptr, raw.size);

	git_buf_free(&raw);
	return error;
}
