timehash_store(const ARTHANDLE article, const STORAGECLASS class) {
    char                *path;
    char                *p;
    time_t              now;
    TOKEN               token;
    int                 fd;
    ssize_t             result;
    int                 seq;
    int                 i;

    if (article.arrived == (time_t)0)
	now = time(NULL);
    else
	now = article.arrived;

    memset(&token, 0, sizeof(token));

    for (i = 0; i < 0x10000; i++) {
	seq = SeqNum;
	SeqNum = (SeqNum + 1) & 0xffff;
	path = MakePath(now, seq, class);

        if ((fd = open(path, O_CREAT|O_EXCL|O_WRONLY, ARTFILE_MODE)) < 0) {
	    if (errno == EEXIST)
		continue;
	    p = strrchr(path, '/');
	    *p = '\0';
	    if (!MakeDirectory(path, true)) {
                syswarn("timehash: could not make directory %s", path);
	        token.type = TOKEN_EMPTY;
	        free(path);
	        SMseterror(SMERR_UNDEFINED, NULL);
	        return token;
	    } else {
	        *p = '/';
	        if ((fd = open(path, O_CREAT|O_EXCL|O_WRONLY, ARTFILE_MODE)) < 0) {
		    SMseterror(SMERR_UNDEFINED, NULL);
                    syswarn("timehash: could not create %s", path);
		    token.type = TOKEN_EMPTY;
		    free(path);
		    return token;
	        }
	    }
        }
	break;
    }
    if (i == 0x10000) {
	SMseterror(SMERR_UNDEFINED, NULL);
        warn("timehash: all sequence numbers for time %lu and class %d are"
             " reserved", (unsigned long) now, class);
	token.type = TOKEN_EMPTY;
	free(path);
	return token;
    }

    result = xwritev(fd, article.iov, article.iovcnt);
    if (result != (ssize_t) article.len) {
	SMseterror(SMERR_UNDEFINED, NULL);
        syswarn("timehash: error writing %s", path);
	close(fd);
	token.type = TOKEN_EMPTY;
	unlink(path);
	free(path);
	return token;
    }
    close(fd);
    free(path);
    return MakeToken(now, seq, class, article.token);
}
