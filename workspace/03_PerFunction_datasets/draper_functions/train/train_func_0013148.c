timecaf_retrieve(const TOKEN token, const RETRTYPE amount) {
    time_t              timestamp;
    ARTNUM              artnum;
    char                *path;
    ARTHANDLE           *art;
    static TOKEN	ret_token;
    time_t		now;

    if (token.type != TOKEN_TIMECAF) {
	SMseterror(SMERR_INTERNAL, NULL);
	return NULL;
    }

    BreakToken(token, &timestamp, &artnum);


    if (SMpreopen && amount == RETR_STAT) {
	now = time(NULL);
	if (timestamp < ((now >> 8) & 0xffffff)) {
	    return StatArticle(timestamp, artnum, token.class);
	}
    }

    path = MakePath(timestamp, token.class);
    if ((art = OpenArticle(path, artnum, amount)) != (ARTHANDLE *)NULL) {
	art->arrived = timestamp<<8;


	ret_token = token;
	art->token = &ret_token;
    }
    free(path);
    return art;
}
