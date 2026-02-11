smtp_mta(char *server, struct name *to, FILE *fi, struct header *hp,
		const char *user, const char *password, const char *skinned)
{
	struct sock	so;
	int	use_ssl, ret;
	sighandler_type	saveterm;

	memset(&so, 0, sizeof so);
	verbose = value("verbose") != NULL;
	_debug = value("debug") != NULL;
	saveterm = safe_signal(SIGTERM, SIG_IGN);
	if (sigsetjmp(smtpjmp, 1)) {
		safe_signal(SIGTERM, saveterm);
		return 1;
	}
	if (saveterm != SIG_IGN)
		safe_signal(SIGTERM, onterm);
	if (strncmp(server, "smtp://", 7) == 0) {
		use_ssl = 0;
		server += 7;
#ifdef	USE_SSL
	} else if (strncmp(server, "smtps://", 8) == 0) {
		use_ssl = 1;
		server += 8;
#endif
	} else
		use_ssl = 0;
	if (!debug && !_debug && sopen(server, &so, use_ssl, server,
				use_ssl ? "smtps" : "smtp", verbose) != OKAY) {
		safe_signal(SIGTERM, saveterm);
		return 1;
	}
	so.s_desc = "SMTP";
	ret = talk_smtp(to, fi, &so, server, server, hp,
			user, password, skinned);
	if (!debug && !_debug)
		sclose(&so);
	if (smtpbuf) {
		free(smtpbuf);
		smtpbuf = NULL;
		smtpbufsize = 0;
	}
	safe_signal(SIGTERM, saveterm);
	return ret;
}
