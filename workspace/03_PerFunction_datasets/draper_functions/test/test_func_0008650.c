imap_preauth(struct mailbox *mp, const char *xserver, const char *uhp)
{
	char	*server, *cp;

	mp->mb_active |= MB_PREAUTH;
	imap_answer(mp, 1);
	if ((cp = strchr(xserver, ':')) != NULL) {
		server = salloc(cp - xserver + 1);
		memcpy(server, xserver, cp - xserver);
		server[cp - xserver] = '\0';
	} else
		server = (char *)xserver;
#ifdef	USE_SSL
	if (mp->mb_sock.s_use_ssl == 0 && imap_use_starttls(uhp)) {
		FILE	*queuefp = NULL;
		char	o[LINESIZE];

		snprintf(o, sizeof o, "%s STARTTLS\r\n", tag(1));
		IMAP_OUT(o, MB_COMD, return STOP);
		IMAP_ANSWER()
		if (ssl_open(server, &mp->mb_sock, uhp) != OKAY)
			return STOP;
	}
#else
	if (imap_use_starttls(uhp)) {
		fprintf(stderr, "No SSL support compiled in.\n");
		return STOP;
	}
#endif
	imap_capability(mp);
	return OKAY;
}
