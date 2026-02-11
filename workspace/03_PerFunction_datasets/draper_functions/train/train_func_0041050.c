gpg_ctx_new (GMimeGpgContext *ctx)
{
	struct _GpgCtx *gpg;
	const char *charset;
	GMimeStream *stream;

	gpg = g_slice_new (struct _GpgCtx);
	gpg->mode = GPG_CTX_MODE_SIGN;
	gpg->ctx = ctx;
	gpg->userid_hint = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
	gpg->decrypt_okay = FALSE;
	gpg->complete = FALSE;
	gpg->seen_eof1 = TRUE;
	gpg->seen_eof2 = FALSE;
	gpg->pid = (pid_t) -1;
	gpg->exit_status = 0;
	gpg->flushed = FALSE;
	gpg->exited = FALSE;

	gpg->userid = NULL;
	gpg->recipients = NULL;
	gpg->cipher = GMIME_CIPHER_ALGO_DEFAULT;
	gpg->digest = GMIME_DIGEST_ALGO_DEFAULT;
	gpg->always_trust = FALSE;
	gpg->use_agent = FALSE;
	gpg->armor = FALSE;

	gpg->stdin_fd = -1;
	gpg->stdout_fd = -1;
	gpg->stderr_fd = -1;
	gpg->status_fd = -1;
	gpg->secret_fd = -1;

	gpg->statusbuf = g_malloc (128);
	gpg->statusptr = gpg->statusbuf;
	gpg->statusleft = 128;

	gpg->bad_passwds = 0;
	gpg->need_passwd = FALSE;
	gpg->need_id = NULL;

	gpg->encrypted_to = NULL;
	gpg->signatures = NULL;
	gpg->signature = NULL;

	gpg->sigstream = NULL;
	gpg->istream = NULL;
	gpg->ostream = NULL;

	stream = g_mime_stream_mem_new ();
	gpg->diag = GMIME_STREAM_MEM (stream)->buffer;
	charset = g_mime_charset_iconv_name (g_mime_locale_charset ());
	if (g_ascii_strcasecmp (charset, "UTF-8") != 0) {
		GMimeStream *fstream;
		GMimeFilter *filter;

		fstream = g_mime_stream_filter_new (stream);
		filter = g_mime_filter_charset_new (charset, "UTF-8");
		g_mime_stream_filter_add ((GMimeStreamFilter *) fstream, filter);
		g_object_unref (stream);
		g_object_unref (filter);

		gpg->diagnostics = fstream;

		gpg->utf8 = FALSE;
	} else {

		gpg->diagnostics = stream;

		gpg->utf8 = TRUE;
	}

	return gpg;
}
