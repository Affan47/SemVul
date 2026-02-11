imap_auth(struct mailbox *mp, const char *uhp, char *xuser, const char *pass)
{
	char	*var;
	char	*auth;

	if (!(mp->mb_active & MB_PREAUTH))
		return OKAY;
	if ((auth = value("imap-auth")) == NULL) {
		var = ac_alloc(strlen(uhp) + 11);
		strcpy(var, "imap-auth-");
		strcpy(&var[10], uhp);
		auth = value(var);
		ac_free(var);
	}
	if (auth == NULL || strcmp(auth, "login") == 0)
		return imap_login(mp, xuser, pass);
	if (strcmp(auth, "cram-md5") == 0)
		return imap_cram_md5(mp, xuser, pass);
	if (strcmp(auth, "gssapi") == 0) {
#ifdef	USE_GSSAPI
		return imap_gss(mp, xuser);
#else
		fprintf(stderr, "No GSSAPI support compiled in.\n");
		return STOP;
#endif
	}
	fprintf(stderr, "Unknown IMAP authentication method: \"%s\"\n", auth);
	return STOP;
}
