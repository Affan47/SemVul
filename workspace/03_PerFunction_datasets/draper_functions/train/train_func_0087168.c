pass_get_password(struct pass_session *passd,
		const char *host, const char *user)
{
    struct pass_session *fts = NULL;
    char *account;

    if (passd == NULL) {
	return NULL;
    }
    if (fts == NULL) {
	account = av_stradd(NULL, user, USER_SEP_STR, host, NULL);
	fts = pass_find_session(passd, account);
	av_free(account);
    }

    if(fts == NULL) {
        account = av_stradd(NULL, user, USER_SEP_STR, NULL);
        fts = pass_find_session(passd, account);
        av_free(account);
    }

    if(fts == NULL) {
        account = av_stradd(NULL, USER_SEP_STR, host, NULL);
        fts = pass_find_session(passd, account);
        av_free(account);
    }

    av_log(AVLOG_DEBUG, "passwords: fts=%lx", (long) fts);
    return fts;
}
